#ifndef LCDD_HITS_TRACKERHIT_HH_
#define LCDD_HITS_TRACKERHIT_HH_ 1

// LCDD
#include "lcdd/id/Id64bit.hh"

// Geant4
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"

/**
 * @brief
 * A tracker hit class that implements the G4VHit interface.
 */
class TrackerHit: public G4VHit {
public:

    /**
     * Class constructor.
     */
    TrackerHit();

    /**
     * Class destructor.
     */
    virtual ~TrackerHit();

    /**
     * Custom new operator.
     */
    inline void *operator new(size_t);

    /**
     * Custom delete operator.
     */
    inline void operator delete(void *aHit);

    /**
     * Draw this hit in Geant4 event display.
     */
#ifdef G4VIS_USE
    void Draw();
#endif

    void Print();

public:

    /**
     * Custom stream operator for printing.
     * @param[in] os  The output stream.
     * @param[in] hit The hit to print.
     */
    friend std::ostream& operator<<(std::ostream &os, const TrackerHit& hit);

    /**
     * Set the time of the hit.
     * @param[in] tdep The time of the hit.
     */
    void setTdep(const G4double tdep);

    /**
     * Set the energy deposition.
     * @param[in] edep The energy deposition.
     */
    void setEdep(const G4double edep);

    /**
     * Set the global position.
     * @param[in] posXYZ The position in global coordinates (mm).
     */
    void setPosition(const G4ThreeVector& posXYZ);

    /**
     * Set the momentum.
     * @param[in] mom The hit's momentum.
     */
    void setMomentum(const G4ThreeVector& mom);

    /**
     * Set the track ID.
     * @param[in] trkID The track ID.
     */
    void setTrackID(const G4int trkID);

    /**
     * Set the PDG.
     * @param[in] pdg The PDG code.
     */
    void setPDG(const G4int pdg);

    /**
     * Set the length of the step.
     * @param[in] l The length of the step.
     */
    void setLength(const G4double l);

    /**
     * Get the global time of the hit.
     * @return The global time of the hit (ns).
     */
    G4double getTdep() const;

    /**
     * Get the energy deposition.
     * @return The energy deposition.
     */
    G4double getEdep() const;

    /**
     * Set the global position.
     * @return The global position.
     */
    G4ThreeVector getPosition() const;

    /**
     * Get the momentum.
     * @return The momentum.
     */
    G4ThreeVector getMomentum() const;

    /**
     * Get the track ID.
     * @return The track ID.
     */
    G4int getTrackID() const;

    /**
     * Get the PDG code.
     * @return The PDG code.
     */
    G4int getPDG() const;

    /**
     * Get the step length.
     * @return The length of the step.
     */
    G4double getLength() const;

    /**
     * Set the ID.
     * @param[id] id1 The ID.
     */
    void setId(Id64bit::ElementType id1);

    /**
     * Get the ID.
     * @return The ID as an int.
     */
    int getId();

public:

    G4double _edep;
    G4double _tdep;
    G4ThreeVector _pos;
    G4ThreeVector _mom;
    G4int _trkID;
    G4int _PDG;
    G4double _length;
    Id64bit _id;
};

/**
 * Template instantiation of G4 hits collection class.
 */
typedef G4THitsCollection<TrackerHit> (TrackerHitsCollection);

/**
 * Memory allocator for objects of this class.
 */
extern G4Allocator<TrackerHit> G4TrackerHitAllocator;

/**
 * Implementation of custom new operator.
 */
inline void* TrackerHit::operator new(size_t) {
    void* aHit;
    aHit = (void*) G4TrackerHitAllocator.MallocSingle();
    return aHit;
}

/**
 * Implementation of custom delete operator.
 */
inline void TrackerHit::operator delete(void *aHit) {
    G4TrackerHitAllocator.FreeSingle((TrackerHit*) aHit);
}

#endif
