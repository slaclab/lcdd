// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/TrackerSD.hh,v 1.8 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_DETECTORS_TRACKERSD_HH
#define LCDD_DETECTORS_TRACKERSD_HH 1

// LCDD
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/hits/TrackerHit.hh"

/**
 * @brief The basic binding for a tracker type subdetector that records individual step information.
 */
class TrackerSD: public SensitiveDetector {

public:

    /**
     * Class constructor.
     * @param[in] sdName The name of the sensitive detector.
     * @param[in] hcName The hit collection name.
     */
    TrackerSD(G4String sdName, std::vector<G4String> hitsCollectionNames);

    /**
     * Class destructor.
     */
    virtual ~TrackerSD();

public:

    /**
     * Perform initialization at start of event.
     * @param[in] hce The hit collection of this event.
     */
    virtual void Initialize(G4HCofThisEvent* hce);

    /**
     * Perform end of event processing.
     * @param[in] hce The hit collection of this event.
     */
    //virtual void EndOfEvent(G4HCofThisEvent* hce);

    /**
     * Clear the current hit list.
     */
    void clearHits();

    /**
     * Add a TrackerHit.
     * @param[in] hit The Tracker hit to add.
     */
    void addHit(TrackerHit* hit, int hcid = 0);

protected:

    /**
     * Process step to produce hits.
     * @param[in] step      The current G4Step object.
     * @param[in] touchable The current touchable handle into the geometry.
     */
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* touchable);

protected:
    std::vector<TrackerHitsCollection*> _hitsCollections;
};

#endif
