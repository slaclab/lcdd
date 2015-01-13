#include "lcdd/detectors/CalorimeterSD.hh"

// LCDD
#include "lcdd/detectors/PositionComparator.hh"
#include "lcdd/id/IdComparator.hh"

// STL
#include <iostream>
#include <string>
#include <vector>

using std::vector;

CalorimeterSD::CalorimeterSD(G4String sdName, G4String hcName, Segmentation* sdSeg) :
        SensitiveDetector(sdName, hcName, SensitiveDetector::eCalorimeter), _segmentation(sdSeg), _ddsegmentation(NULL) {
    // Setup a dummy hits collection that will be overridden later.
    _hitsCollections.push_back(NULL);
}

CalorimeterSD::CalorimeterSD(G4String sdName, const vector<G4String>& hcNames, Segmentation* sdSeg) :
        SensitiveDetector(sdName, hcNames, SensitiveDetector::eCalorimeter), _segmentation(sdSeg), _ddsegmentation(NULL) {
    // Setup entries for each hits collection.  These null pointers will be overridden later.
    for (int i = 0; i < (int) hcNames.size(); i++) {
        _hitsCollections.push_back(NULL);
    }
}

/*
CalorimeterSD::CalorimeterSD(
        G4String sensitiveDetectorName,
        const vector<G4String>& hitsCollectionNames,
        DD4hep::DDSegmentation::Segmentation* segmentation) :
        SensitiveDetector(sensitiveDetectorName, hitsCollectionNames, SensitiveDetector::eCalorimeter), _ddsegmentation(segmentation) {
    for (int i = 0; i < (int) hitsCollectionNames.size(); i++) {
        _hitsCollections.push_back(NULL);
    }
}
*/

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

    // Loop over number of hits collections defined by this detector.
    for (int i = 0; i < getNumberOfHitsCollections(); i++) {

        //std::cout << "initializing hits collection: " << collectionName[i] << std::endl;

        // Overwrite dummy collection with actual calorimeter hits collection.
        _hitsCollections[i] = new CalorimeterHitsCollection(GetName(), collectionName[i]);

        // Set the HCID of the collection if it has not been set already.
        if (getHCID(i) < 0) {
            // This will set the HC ID in the list that is contained in SensitiveDetector parent class.
            setHCID(GetCollectionID(i), i);
        }

        // Add the hits collection to the hits collections of the event.
        HCE->AddHitsCollection(getHCID(i), _hitsCollections[i]);

        // Add a hit map for this collection.
        _hitMaps.push_back(new CalorimeterHitMap());
    }
}

void CalorimeterSD::setDDSegmentation(DD4hep::DDSegmentation::Segmentation* ddsegmentation) {
    _ddsegmentation = ddsegmentation;
}

Segmentation* CalorimeterSD::getSegmentation() const {
    return _segmentation;
}

DD4hep::DDSegmentation::Segmentation* CalorimeterSD::getDDSegmentation() const {
    return _ddsegmentation;
}

G4bool CalorimeterSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    return SensitiveDetector::ProcessHits(aStep, 0);
}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent *) {

    // Delete hit maps.
    for (unsigned int i=0; i<_hitMaps.size(); i++) {
        delete _hitMaps[i];
    }

    // Clear list of hit maps.
    _hitMaps.clear();
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

void CalorimeterSD::addHit(CalorimeterHit* hit, int collectionIndex) {
    _hitsCollections[collectionIndex]->insert(hit);
    _hitMaps[collectionIndex]->add(hit);
}

CalorimeterHit* CalorimeterSD::findHit(const Id64bit& id, int collectionIndex) {
    return _hitMaps[collectionIndex]->get(id);
}

CalorimeterHitMap* CalorimeterSD::getCalorimeterHitMap(int collectionIndex) {
    return _hitMaps[collectionIndex];
}
