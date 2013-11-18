// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/OpticalCalorimeterHitProcessor.cc,v 1.7 2013-11-14 00:46:45 jeremy Exp $

// LCDD
#include "lcdd/detectors/OpticalCalorimeterHitProcessor.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4OpticalPhoton.hh"
#include "G4TransportationManager.hh"
#include "G4VProcess.hh"
#include "G4Poisson.hh"

OpticalCalorimeterHitProcessor::OpticalCalorimeterHitProcessor(CalorimeterSD* calorimeter) :
        LegacyCalorimeterHitProcessor(calorimeter), _cerenGenerator(0) {
}

OpticalCalorimeterHitProcessor::~OpticalCalorimeterHitProcessor() {
    if (_cerenGenerator != 0) {
        delete _cerenGenerator;
    }
}

bool OpticalCalorimeterHitProcessor::processHits(G4Step* step) {
    // FIXME: This initialization should not happen here.
    //        Put into PhysicsManager as statically accessible.
    if (_cerenGenerator == 0) {
        _cerenGenerator = new Cerenkov();
    }

    G4int NCerenPhotons = 0;
    G4Track* theTrack = step->GetTrack();
    const G4double charge = theTrack->GetDefinition()->GetPDGCharge();
    G4StepPoint* pPreStepPoint = step->GetPreStepPoint();
    G4StepPoint* pPostStepPoint = step->GetPostStepPoint();
    G4double beta = 0.5 * (pPreStepPoint->GetBeta() + pPostStepPoint->GetBeta());
    const G4VTouchable* touch = step->GetPreStepPoint()->GetTouchable();
    G4String thematerial = touch->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName();
    G4double MeanNumberOfPhotons = _cerenGenerator->GetAverageNumberOfPhotons(charge, beta, thematerial);
    if (MeanNumberOfPhotons > 0.0) {
        G4double step_length = step->GetStepLength();
        MeanNumberOfPhotons = MeanNumberOfPhotons * step_length;
        NCerenPhotons = (G4int) G4Poisson(MeanNumberOfPhotons);
    } else {
        NCerenPhotons = 0;
    }

    if (NCerenPhotons <= 0) {
        return LegacyCalorimeterHitProcessor::processHits(step);
    } else {
        G4ThreeVector myPoint = step->GetPreStepPoint()->GetPosition();
        G4StepPoint* apreStepPoint = step->GetPreStepPoint();
        G4double theEdep = double(NCerenPhotons);
        // get global cell pos from seg
        G4ThreeVector globalCellPos = getGlobalHitPosition(apreStepPoint);
        // reset the seg bins
        _calorimeter->getSegmentation()->resetBins();
        // set the seg bins
        _calorimeter->getSegmentation()->setBins(step);

        // Create an identifier.
        Id64bit id64 = _calorimeter->makeIdentifier(step);

        // Look for existing hit.
        CalorimeterHit* hit = _calorimeter->findHit(id64);

        // Was hit found?
        if (hit == 0) {

            // Hit was not found, so new one is created.
            hit = new CalorimeterHit(id64, theEdep, globalCellPos);

            // Add hit to calorimeter.
            _calorimeter->addHit(hit, eCerenkov);
        } else {
            // Add energy deposition to existing hit.
            hit->addEdep(theEdep);
        }
        // add McpHitContrib to this hit, setting info from step info
        hit->addHitContribution(HitContribution(step));
        return true;
    }  // end Cerenkov photon treatment
}

G4ThreeVector OpticalCalorimeterHitProcessor::getGlobalHitPosition(const G4StepPoint* aPreStepPoint) {
    G4ThreeVector globalStepPos = aPreStepPoint->GetPosition();

    // Figure out local step pos using touchable and global midpoint.
    G4ThreeVector localStepPos = ReadoutUtil::transformGlobalToLocal(aPreStepPoint, globalStepPos);

    // Compute local cell pos.
    G4ThreeVector localCellPos = _calorimeter->getSegmentation()->getLocalHitPosition(localStepPos);

    // Compute global cell pos.
    G4ThreeVector globalCellPos = ReadoutUtil::transformLocalToGlobal(aPreStepPoint, localCellPos);

    return globalCellPos;
}

