#include "lcdd/detectors/TrackerSD.hh"

// STL
#include <iostream>

TrackerSD::TrackerSD(G4String sdName, std::vector<G4String> hitsCollectionNames) :
        SensitiveDetector(sdName, hitsCollectionNames, SensitiveDetector::eTracker) {
    // The actual pointers to the collections are overridden later in Initialize.
    for (int i = 0; i < (int) hitsCollectionNames.size(); i++) {
        _hitsCollections.push_back(0);
    }
}

TrackerSD::~TrackerSD() {
}

void TrackerSD::Initialize(G4HCofThisEvent *HCE) {
    // Loop over number of hits collections defined by this detector.
    for (int i = 0; i < getNumberOfHitsCollections(); i++) {

        // Overwrite pointer to the dummy collection that was added in the constructor.
        _hitsCollections[i] = new TrackerHitsCollection(GetName(), collectionName[i]);

        if (getHCID(i) < 0) {
            // Set the HCID.
            setHCID(GetCollectionID(i), i);
        }

        // Add the hits collection to the Geant4 HCE.
        HCE->AddHitsCollection(getHCID(i), _hitsCollections[i]);
    }
}

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // Call parent class's method which will activate registered HitProcessors.
    return SensitiveDetector::ProcessHits(aStep, 0);
}

void TrackerSD::addHit(TrackerHit* hit, int hcid) {
    _hitsCollections[hcid]->insert(hit);
}
