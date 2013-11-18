// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/TrackerSD.cc,v 1.7 2013-11-13 23:02:56 jeremy Exp $

// LCDD
//#include "lcdd/id/IdManager.hh"
//#include "lcdd/id/IdFactory.hh"
//#include "lcdd/id/IdVec.hh"
#include "lcdd/detectors/TrackerSD.hh"

// STL
#include <iostream>

TrackerSD::TrackerSD(G4String sdName, std::vector<G4String> hitsCollectionNames) :
        SensitiveDetector(sdName, hitsCollectionNames, SensitiveDetector::eTracker)
//, _HC(0)
{
    //_hits.clear();
    // The actual pointers to the collections are overridden later in Initialize.
    for (int i = 0; i < (int) hitsCollectionNames.size(); i++) {
        _hitsCollections.push_back(0);
    }
}

TrackerSD::~TrackerSD() {
}

/*
 void TrackerSD::Initialize(G4HCofThisEvent *HCE)
 {
 clearHits();

 // create tracker hits coll
 _HC = new G4TrackerHitsCollection(GetName(), collectionName[0]);

 // set HCID
 if (getHCID() < 0) {
 setHCID(GetCollectionID(0));
 }

 // add collection to HC of event
 HCE->AddHitsCollection(getHCID(), _HC);
 }
 */

void TrackerSD::Initialize(G4HCofThisEvent *HCE) {
    // Loop over number of hits collections defined by this detector.
    for (int i = 0; i < getNumberOfHitsCollections(); i++) {

        //std::cout << "TrackerSD::Initialize - initializing hits collection <" << collectionName[i] << ">" << std::endl;

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

std::ostream& TrackerSD::printHits(std::ostream& os) {
    /*
     for (G4TrackerHitList::const_iterator iter = _hits.begin(); iter != _hits.end(); iter++) {
     os << (*(const_cast<const TrackerHit*>(*iter)));
     }
     os << std::endl;
     */
    return os;
}

void TrackerSD::EndOfEvent(G4HCofThisEvent *) {
    /*
     #ifdef G4VERBOSE
     if ( getVerbose() > 0 ) {
     std::cout << GetName() << " has " << _HC->GetSize() << " hits." << std::endl;
     }

     if ( getVerbose() > 1 ) {
     printHits ( std::cout );
     }
     #endif
     */

    clearHits();
}

double TrackerSD::getEdep() const {
    double edep = 0.0;
    /*
     for (G4TrackerHitList::const_iterator it = _hits.begin(); it != _hits.end(); it++) {
     edep += (*it)->getEdep();
     }
     */
    return edep;
}

void TrackerSD::clearHits() {
    //_hits.clear();
}

void TrackerSD::addHit(TrackerHit* hit, int hcid) {
    _hitsCollections[hcid]->insert(hit);
}
