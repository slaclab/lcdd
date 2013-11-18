// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/Cerenkov.hh,v 1.6 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_CERENKOV_HH
#define LCDD_DETECTORS_CERENKOV_HH 1

// Geant4
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4Material.hh" 
#include "G4MaterialPropertyVector.hh"

// STL
#include <vector>

/**
 * @class Cerenkov
 * @brief A physics utility class modeling optical photon production.
 * @author Hans Wenzel
 */
class Cerenkov {
public:

    /**
     * Class constructor.
     */
    Cerenkov();

    /**
     * Class destructor.
     */
    ~Cerenkov();

    /**
     * Initialize the Cerenkov data.
     */
    void Initialize();

    /**
     * Compute average number of photons.
     * @param[in] charge   The particle PDG charge value.
     * @param[in] beta     Velocity of the track in unit of c (light velocity).
     * @param[in] material The name of the G4Material.
     */
    G4double GetAverageNumberOfPhotons(const G4double charge, const G4double beta, const G4String material) const;

private:
    std::vector<G4String> _CAI;
    std::vector<G4PhysicsOrderedFreeVector*> _cerenkovAngleIntegrals;
    std::vector<G4MaterialPropertyVector*> _refractionIndeces;
};

#endif

