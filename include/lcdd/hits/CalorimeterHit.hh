#ifndef LCDD_HITS_CALORIMETERHIT_HH_
#define LCDD_HITS_CALORIMETERHIT_HH_ 1

// LCDD
#include "lcdd/id/Id64bit.hh"
#include "lcdd/hits/HitContribution.hh"

// Geant4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

// STL
#include <iostream>

/**
 * @brief This class is an implementation of G4VHit for calorimeter hits.
 * @todo The endcap flag should be on the collection only, not individual hits.
 */
class CalorimeterHit: public G4VHit {

public:

    /**
     * Class constructor.
     */
    CalorimeterHit();

    /**
     * Class destructor.
     */
    virtual ~CalorimeterHit();

    /**
     * Copy constructor.
     */
    CalorimeterHit(const CalorimeterHit &right);

    /**
     * Qualified constructor.
     * @param[in] id            The 64-bit id.
     * @param[in] edep          The energy deposition.
     * @param[in] globalCellPos The global position.
     */
    CalorimeterHit(Id64bit id, G4double edep, G4ThreeVector globalCellPos);

    /**
     * Operator overloading for setting contents from another hit.
     */
    const CalorimeterHit& operator=(const CalorimeterHit &right);

    /**
     * Operator overloading for comparison of hits.
     */
    bool operator==(const CalorimeterHit &right);

    /**
     * Custom new method.
     */
    inline void *operator new(size_t);

    /**
     * Custom delete method.
     */
    inline void operator delete(void *aHit);

#ifdef G4VIS_USE
    void Draw();
#endif

    /**
     * Print the hit contributions.
     * @param[in] os The output stream.
     */
    void printHitContributions(std::ostream& os);

    /**
     * Print the hit contribution header.
     * @param[in] os The output stream.
     */
    void printHitContributionsHeader(std::ostream&);

    /**
     * Print the contents of this hit.
     */
    void Print();

    /**
     * Operator overloading of stream operator for printing.
     * @param[in] os  The output stream.
     * @param[in] hit The hit to print.
     */
    friend std::ostream& operator<<(std::ostream &os, const CalorimeterHit& hit);

    /**
     * Set the hit's position.
     * @param[in] posXYZ The hit's global position.
     */
    void setPosition(const G4ThreeVector& posXYZ);

    /**
     * Set the energy deposition.
     * @param[in] e The energy deposition (GeV).
     */
    void setEdep(const G4double e);

    /**
     * Increment the energy deposition by some amount.
     * @param[in] e The amount to increment the energy (GeV).
     */
    void addEdep(const G4double e);

    /**
     * Get the global position of the hit.
     * @return The global position of the hit.
     */
    G4ThreeVector getPosition() const;

    /**
     * Get the energy deposition of this hit.
     * @return The hit's energy deposition.
     */
    G4double getEdep() const;

    /**
     * Add a hit contribution.
     * @param[in] contrib The hit contribution.
     */
    void addHitContribution(HitContribution contrib);

    /**
     * Get the list of hit contributions.
     * @return The list of hit contributions.
     */
    const HitContributionList& getHitContributions() const;

    /**
     * Get the 64-bit ID.
     * @return The 64-bit ID.
     */
    const Id64bit& getId64bit() const;

    /**
     * Set the endcap flag.
     * @param[in] ec The endcap flag.
     */
    void setEndcapFlag(bool ec = true);

    /**
     * Get the endcap flag.
     * @return The endcap flag.
     */
    bool getEndcapFlag();

private:

    // 64-bit id.
    Id64bit _id;

    // Energy deposition.
    G4double _edep;

    // Position.
    G4ThreeVector _pos;

    // Endcap flag.
    bool _endcap;

    // List of contributions by MCParticle.
    HitContributionList _particleList;
};

typedef G4THitsCollection<CalorimeterHit> (CalorimeterHitsCollection);

extern G4Allocator<CalorimeterHit> CalorimeterHitAllocator;

/**
 * Implementation of custom new operator.
 */
inline void* CalorimeterHit::operator new(size_t) {
    void* aHit;
    aHit = (void*) CalorimeterHitAllocator.MallocSingle();
    return aHit;
}

/**
 * Implementation of custom delete operator.
 */
inline void CalorimeterHit::operator delete(void *aHit) {
    CalorimeterHitAllocator.FreeSingle((CalorimeterHit*) aHit);
}

#endif
