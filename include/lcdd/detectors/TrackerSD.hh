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

    //typedef std::vector<TrackerHit*> TrackerHitList;

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
    virtual void EndOfEvent(G4HCofThisEvent* hce);

    /**
     * Print out hit data.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    std::ostream& printHits(std::ostream& os);

    /**
     * Get the total energy deposition in the event.
     * @return The total energy deposition.
     */
    double getEdep() const;

    /**
     * Clear the current hit list.
     */
    void clearHits();

    /**
     * Get the list of tracker hits.
     * @return The list of tracker hits.
     */
    //G4TrackerHitList getTrackerHitList();
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
    //G4TrackerHitsCollection* _HC;
    //G4TrackerHitList _hits;
    std::vector<TrackerHitsCollection*> _hitsCollections;
};

#endif
