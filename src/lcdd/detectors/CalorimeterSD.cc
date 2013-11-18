// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/CalorimeterSD.cc,v 1.12 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/CalorimeterSD.hh"
#include "lcdd/detectors/PositionComparator.hh"
#include "lcdd/id/IdComparator.hh"

// STL
#include <iostream>
#include <string>
#include <vector>

using std::vector;

CalorimeterSD::CalorimeterSD(G4String sdName, G4String hcName, Segmentation* sdSeg) :
        SensitiveDetector(sdName, hcName, SensitiveDetector::eCalorimeter), _segmentation(sdSeg) {
    // Setup a dummy hits collection that will be overridden later.
    _hitsCollections.push_back(0);
}

CalorimeterSD::CalorimeterSD(G4String sdName, const vector<G4String>& hcNames, Segmentation* sdSeg) :
        SensitiveDetector(sdName, hcNames, SensitiveDetector::eCalorimeter), _segmentation(sdSeg) {
    // Setup entries for each hits collection.  These null pointers will be overridden later.
    for (int i = 0; i < (int) hcNames.size(); i++) {
        _hitsCollections.push_back(0);
    }
}

CalorimeterSD::~CalorimeterSD() {
}

bool CalorimeterSD::isValidVolume(G4LogicalVolume* lv) {
    bool valid = SensitiveDetector::isValidVolume(lv);

    if (valid && _segmentation != 0) {
        valid = _segmentation->isValidSolid(lv->GetSolid());
    }

    return valid;
}

void CalorimeterSD::Initialize(G4HCofThisEvent *HCE) {
    clearHits();

    // Loop over number of hits collections defined by this detector.
    for (int i = 0; i < getNumberOfHitsCollections(); i++) {

        //std::cout << "initializing hits collection: " << collectionName[i] << std::endl;

        // Overwrite dummy collection with actual calorimeter hits collection.
        _hitsCollections[i] = new CalorimeterHitsCollection(GetName(), collectionName[i]);

        // Set the HCID of the collection if it has not been set already.
        if (getHCID(i) < 0) {
            //std::cout << "set HCID: " << GetCollectionID(i) << std::endl;
            // This will set the HC ID in the list that is contained in SensitiveDetector parent class.
            setHCID(GetCollectionID(i), i);
        }

        // Add the hits collection to the hits collections of the event.
        HCE->AddHitsCollection(getHCID(i), _hitsCollections[i]);
    }
}

Segmentation* CalorimeterSD::getSegmentation() const {
    return _segmentation;
}

G4bool CalorimeterSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    return SensitiveDetector::ProcessHits(aStep, 0);
}

//CalorimeterHit* CalorimeterSD::findHit(CalorimeterHit* aHit)
//{
//	return _hitMap.get(aHit->getId64bit());
//}

//CalorimeterHit* CalorimeterSD::findHit(CalorimeterHit* aHit, G4int nHC)
//{
//    return _hitMap.get(aHit->getId64bit());
//}

std::ostream& CalorimeterSD::printHits(std::ostream& os) {
    // FIXME: reimplement
    /*
     for (int i = 0; i < getNumberOfHitsCollections(); i++) {
     os << getHitsCollection(i)->GetName() << std::endl;
     for (CalorimeterHitList::const_iterator iter = _hitsVector[i].begin(); iter != _hitsVector[i].end(); iter++) {
     os << "    " << **iter;
     }
     }
     os << std::endl;
     */
    return os;
}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent *) {
#ifdef G4VERBOSE
    if ( getVerbose() > 1 ) {
        printHits( std::cout );
    }
#endif

    _hitMap.clear();
}

std::ostream& CalorimeterSD::printBasicInfo(std::ostream& os) {
    SensitiveDetector::printBasicInfo(os);
    os << "segmentation type: " << _segmentation->getTypeString() << std::endl;
    os << "segmentation bins:";
    for (std::vector<std::string>::const_iterator it = _segmentation->getBinNames().begin(); it != _segmentation->getBinNames().end(); it++) {
        os << " " << *it;
    }
    os << std::endl;
    return os;
}

double CalorimeterSD::getEdep() const {
    // FIXME: reimplement
    /*
     double edep = 0.0;
     for (CalorimeterHitList::const_iterator it = _hitsVector[0].begin(); it != _hitsVector[0].end(); it++) {
     edep += (*it)->getEdep();
     }
     return edep;
     */
    return 0.;
}

double CalorimeterSD::getEdep(G4int nHC) const {
    // FIXME: reimplement
    /*
     double edep = 0.0;
     for (CalorimeterHitList::const_iterator it = _hitsVector[nHC].begin(); it != _hitsVector[nHC].end(); it++) {
     edep += (*it)->getEdep();
     }
     return edep;
     */
    return 0.;
}

void CalorimeterSD::clearHits() {
    //for (int i = 0; i < getNumberOfHitsCollections(); i++) {
    //    _hitsVector[i].clear();
    //}
}

void CalorimeterSD::addHit(CalorimeterHit* hit) {
    _hitsCollections[0]->insert(hit);
    _hitMap.add(hit);
}

void CalorimeterSD::addHit(CalorimeterHit* hit, int collectionIndex) {
    //std::cout << "adding hit" << hit << " to collection " << collectionIndex << std::endl;
    _hitsCollections[collectionIndex]->insert(hit);
    //std::cout << "adding hit to map" << std::endl;
    _hitMap.add(hit);
    //std::cout << "done adding hit" << std::endl;
}

//CalorimeterHit* CalorimeterSD::findHit(const Id64bit& id) {
//    return _hitMap.get(id);
//}

CalorimeterHit* CalorimeterSD::findHit(const Id64bit& id) {
    return _hitMap.get(id);
}
