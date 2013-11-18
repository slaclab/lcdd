// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/hits/HitContribution.hh,v 1.6 2013-11-14 00:47:20 jeremy Exp $
#ifndef LCDD_HITS_HITCONTRIBUTION_HH
#define LCDD_HITS_HITCONTRIBUTION_HH 1

// Geant4
#include "globals.hh"
#include "G4ThreeVector.hh"

// STL
#include <vector>
#include <iostream>

// SLIC
class CalorimeterHit;

// Geant4
class G4Step;

/**
 * @brief Contribution of an MCParticle to a hit.
 * @note Used by CalorimeterHit class.
 */
class HitContribution {
public:
    friend class CalorimeterHit;

public:

    /**
     * Class constructor.
     */
    HitContribution();

    /**
     * Fully qualified constructor.
     * @param[in] trackID    The Geant4 track ID.
     * @param[in] edep       The energy deposition (GeV).
     * @param[in] PDGID      The PDG code of the contributing particle.
     * @param[in] globalTime The global time of the contribution (ns).
     */
    HitContribution(G4int trackID, G4double edep, G4int PDGID, G4double globalTime);

    /**
     * Constructor based on step information.
     */
    HitContribution(const G4Step* aStep);

    /**
     * Class destructor.
     */
    virtual ~HitContribution();

    /**
     * Get the track ID.
     * @return The track ID.
     */
    G4int getTrackID() const;

    /**
     * Get the energy deposition.
     * @return The energy deposition (GeV).
     */
    G4double getEdep() const;

    /**
     * Increment the current energy deposition.
     * @param[in] incr The amount to increment by.
     */
    void incrEdep(G4double incr);

    /**
     * Get the PDG code.
     * @return The PDG code.
     */
    G4int getPDGID() const;

    /**
     * Get the global time.
     * @return The global time (ns).
     */
    G4double getGlobalTime() const;

    /**
     * Set the minimum e.g. global time.
     * @param[in] newTime The minimum time.
     */
    void setMinTime(G4double newTime);

    /**
     * Get the position.
     * @return The position as a float array of length 3.
     */
    const float* getPosition() const;

    /**
     * Print out the contribution information to an output stream.
     * @param[in] os The output stream.
     */
    void printOut(std::ostream& os);

private:

    G4int _trackID;
    G4double _edep;
    G4int _PdgId;
    G4double _globalTime;
    float _position[3];
};

typedef std::vector<HitContribution> HitContributionList;

#endif
