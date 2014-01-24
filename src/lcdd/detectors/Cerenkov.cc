///////////////////////////////////////////////////////////////////////
// Class to calculate Number of photons created by Cerenkov Radiation
////////////////////////////////////////////////////////////////////////
//  Hans Wenzel
//
//  The algorithm is stripped from the geant 4 class
//  G4Cerenkov.cc 
//  but since we are only interested in the number of photons created don't need to 
//  actually create optical phtons and put them on the stack. 
//--------------------------------------------------------------------------------------

// LCDD
#include "lcdd/detectors/Cerenkov.hh"

// Geant4
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include <iomanip>

Cerenkov::Cerenkov() {
    Initialize();
}

Cerenkov::~Cerenkov() {

}

void Cerenkov::Initialize() {
    //
    // now get the Cerenkov Angle Integrals for all materials that have the refraction index defined
    //
    const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
    G4int numOfMaterials = G4Material::GetNumberOfMaterials();
    for (G4int i = 0; i < numOfMaterials; i++) {
        // Retrieve vector of refraction indices for the material
        // from the material's optical properties table
        G4Material* aMaterial = (*theMaterialTable)[i];
        G4MaterialPropertiesTable* aMaterialPropertiesTable = aMaterial->GetMaterialPropertiesTable();
        G4PhysicsOrderedFreeVector* CerAngleIntegrals = new G4PhysicsOrderedFreeVector();
        if (aMaterialPropertiesTable) {
            G4MaterialPropertyVector* theRefractionIndexVector = aMaterialPropertiesTable->GetProperty("RINDEX");
            if (theRefractionIndexVector) {
                // Retrieve the first refraction index in vector
                // of (photon energy, refraction index) pairs
                G4double currentRI = (*theRefractionIndexVector)[0];
                if (currentRI > 1.0) {
                    // Create first (photon energy, Cerenkov Integral) pair
                    G4double currentPM = theRefractionIndexVector->Energy(0);
                    G4double currentCAI = 0.0;
                    CerAngleIntegrals->InsertValues(currentPM, currentCAI);
                    // Set previous values to current ones prior to loop
                    G4double prevPM = currentPM;
                    G4double prevCAI = currentCAI;
                    G4double prevRI = currentRI;
                    // loop over all (photon energy, refraction index)
                    // pairs stored for this material
                    for (size_t ii = 1; ii < theRefractionIndexVector->GetVectorLength(); ii++) {
                        currentRI = (*theRefractionIndexVector)[ii];
                        currentPM = theRefractionIndexVector->Energy(ii);
                        currentCAI = 0.5 * (1.0 / (prevRI * prevRI) + 1.0 / (currentRI * currentRI));
                        currentCAI = prevCAI + (currentPM - prevPM) * currentCAI;
                        CerAngleIntegrals->InsertValues(currentPM, currentCAI);
                        prevPM = currentPM;
                        prevCAI = currentCAI;
                        prevRI = currentRI;
                    }
                }
                G4cout << "Material:  " << aMaterial->GetName() << G4endl;
                G4cout << "Refraction Index: " << G4endl;
                G4cout << "=================" << G4endl;
                theRefractionIndexVector->DumpValues();
                G4cout << "Cerenkov angle Integrals: " << G4endl;
                G4cout << "=========================" << G4endl;
                CerAngleIntegrals->DumpValues();
                _CAI.push_back(aMaterial->GetName());
                _cerenkovAngleIntegrals.push_back(CerAngleIntegrals);
                _refractionIndeces.push_back(theRefractionIndexVector);
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// This routine computes the number of Cerenkov photons produced per
// GEANT-unit (millimeter) in the current medium.
//             ^^^^^^^^^^

G4double Cerenkov::GetAverageNumberOfPhotons(const G4double charge, const G4double beta, const G4String Material) const {
    G4bool Ceren = false;
    G4int MaterialIndex = -1;
    //
    // check if optical properties are defined for this material:
    //
    for (unsigned int ii = 0; ii < _CAI.size(); ii++) {
        if (_CAI[ii] == Material) {
            MaterialIndex = ii;
            Ceren = true;
            break;
        }
    }
    if (!Ceren)
        return 0.0;
    const G4double Rfact = 369.81 / (eV * cm);
    if (beta <= 0.0)
        return 0.0;
    if (abs(charge) == 0.0)
        return 0.0;

    G4double BetaInverse = 1. / beta;
    // Min and Max photon energies
    G4double Pmin = _refractionIndeces[MaterialIndex]->GetMinLowEdgeEnergy();
    G4double Pmax = _refractionIndeces[MaterialIndex]->GetMaxLowEdgeEnergy();

    // Min and Max Refraction Indices
    G4double nMin = _refractionIndeces[MaterialIndex]->GetMinValue();
    G4double nMax = _refractionIndeces[MaterialIndex]->GetMaxValue();

    // Max Cerenkov Angle Integral
    G4double CAImax = _cerenkovAngleIntegrals[MaterialIndex]->GetMaxValue();
    G4double dp, ge;

    // If n(Pmax) < 1/Beta -- no photons generated

    if (nMax < BetaInverse) {
        dp = 0;
        ge = 0;
    }    // otherwise if n(Pmin) >= 1/Beta -- photons generated

    else if (nMin > BetaInverse) {
        dp = Pmax - Pmin;
        ge = CAImax;
    }    // If n(Pmin) < 1/Beta, and n(Pmax) >= 1/Beta, then
         // we need to find a P such that the value of n(P) == 1/Beta.
         // Interpolation is performed by the GetEnergy() and
         // Value() methods of the G4MaterialPropertiesTable and
         // the GetValue() method of G4PhysicsVector.

    else {
        Pmin = _refractionIndeces[MaterialIndex]->GetEnergy(BetaInverse);
        dp = Pmax - Pmin;

        // need boolean for current implementation of G4PhysicsVector
        // ==> being phased out
        G4bool isOutRange;
        G4double CAImin = _cerenkovAngleIntegrals[MaterialIndex]->GetValue(Pmin, isOutRange);
        ge = CAImax - CAImin;
    }

    // Calculate number of photons
    G4double NumPhotons = Rfact * charge / eplus * charge / eplus * (dp - ge * BetaInverse * BetaInverse);
    return NumPhotons;
}

