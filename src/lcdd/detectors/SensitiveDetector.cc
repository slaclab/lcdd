#include "lcdd/detectors/SensitiveDetector.hh"

// LCDD
#include "lcdd/id/IdManager.hh"
#include "lcdd/id/IdFactory.hh"
#include "lcdd/detectors/SensitiveDetectorMessenger.hh"

// Geant4
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4UImessenger.hh"
#include "G4VHitsCollection.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UnitsTable.hh"

// STL
#include <iostream>
#include <vector>

using std::vector;

const std::string& SensitiveDetector::TRACKER = "tracker";
const std::string& SensitiveDetector::CALORIMETER = "calorimeter";
const std::string& SensitiveDetector::UNKNOWN = "unknown";

SensitiveDetector::SensitiveDetector(G4String sdName, G4String hcName, EType sdType) :
        G4VSensitiveDetector(sdName), _idspec(0), _type(sdType) {
    // insert hits collection name into SD's name vector
    collectionName.insert(hcName);

    // register detector with G4SDManager
    G4SDManager::GetSDMpointer()->AddNewDetector(this);

    // Create the command messenger.
    _messenger = new SensitiveDetectorMessenger(this);

    // Only one HC 
    _hcids.clear(); // Is this needed???
    _hcids.push_back(-1);
}

SensitiveDetector::SensitiveDetector(G4String sdName, const vector<G4String>& hcNames, EType sdType) :
        G4VSensitiveDetector(sdName), _idspec(0), _type(sdType) {
    _hcids.clear(); // Is this needed???

    for (int i = 0; i < (int) hcNames.size(); i++) {
        // insert hits collection name into SD's name vector
        collectionName.insert(hcNames[i]);
        _hcids.push_back(-1);
    }

    // register detector with G4SDManager 
    G4SDManager::GetSDMpointer()->AddNewDetector(this);

    // Create the command messenger.
    _messenger = new SensitiveDetectorMessenger(this);
}

SensitiveDetector::~SensitiveDetector() {
    // Delete registered HitProcessors.
    for (HitProcessors::iterator it = _hitProcessors.begin(); it != _hitProcessors.end(); it++) {
        delete (*it);
    }
}

void SensitiveDetector::Initialize(G4HCofThisEvent*) {
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // Set the cached step data.
    setStep(aStep);

    // Call the processHits() methods of the registered HitProcessors.
    bool madeHits = false;
    for (HitProcessors::iterator it = _hitProcessors.begin(); it != _hitProcessors.end(); it++) {
        bool processorMadeHit = (*it)->processHits(aStep);
        if (processorMadeHit == true && madeHits == false) {
            madeHits = true;
        }
    }

    // This will return true if at least one processor created a hit.
    return madeHits;
}

const std::string& SensitiveDetector::getTypeString() const {
    if (_type == eTracker) {
        return TRACKER;
    } else if (_type == eCalorimeter) {
        return CALORIMETER;
    } else {
    	return UNKNOWN;
    }
}

std::ostream& SensitiveDetector::printBasicInfo(std::ostream& os) {
    os << "name: " << GetName() << std::endl;
    os << "type: " << _type << std::endl;
    os << "hits collection: " << this->getHCName() << std::endl;
    os << "hits collection ID: " << _hcids[0] << std::endl;
    os << "energy cut: " << G4BestUnit(_ecut, "Energy") << std::endl;
    os << "endcap flag: " << _endcap << std::endl;
    os << "verbose level: " << _verbose << std::endl;

    if (_idspec != 0) {
        os << "id spec: " << _idspec->getName() << std::endl;
        os << "id fields:";
        for (IdSpec::IdFields::const_iterator it = _idspec->IdFieldsBegin(); it != _idspec->IdFieldsEnd(); it++) {
            os << " " << (*it)->getLabel();
        }
        os << std::endl;
    } else {
        os << "No idspec for this detector." << std::endl;
    }

    return os;
}

Id64bit SensitiveDetector::makeIdentifier(G4Step* step) const {
    Id64bit id64;
    if (hasIdSpec()) {

        // get idvec ordered by this idspec
        const IdVec ids = IdFactory::createOrderedIdVec(step, this);

        // pack into 64 bit cell id
        id64 = IdFactory::createIdentifier(ids, getIdSpec());
    }

    return id64;
}

G4VHitsCollection* SensitiveDetector::getHitsCollection() const {
    G4VHitsCollection* hc = 0;
    if (this->getHCID() != -1) {
        hc = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetHCofThisEvent()->GetHC(this->getHCID());
    }
    return hc;
}

G4VHitsCollection* SensitiveDetector::getHitsCollection(G4int nHC) const {
    G4VHitsCollection* hc = 0;
    if (this->getHCID(nHC) != -1) {
        hc = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetHCofThisEvent()->GetHC(this->getHCID(nHC));
    }
    return hc;
}

std::vector<G4LogicalVolume*> SensitiveDetector::getLogicalVolumes() const {
    std::vector<G4LogicalVolume*> volumes;
    for (G4LogicalVolumeStore::const_iterator it = G4LogicalVolumeStore::GetInstance()->begin(); it != G4LogicalVolumeStore::GetInstance()->end();
            it++) {
        if ((*it)->GetSensitiveDetector() == this) {
            volumes.push_back(*it);
        }
    }
    return volumes;
}

std::ostream& SensitiveDetector::printVolumes(std::ostream& os) {
    std::vector<G4LogicalVolume*> volumes = this->getLogicalVolumes();

    for (std::vector<G4LogicalVolume*>::const_iterator it = volumes.begin(); it != volumes.end(); it++) {
        std::cout << (*it)->GetName() << std::endl;
    }
    return os;
}

SensitiveDetector::EType SensitiveDetector::getType() const {
    return _type;
}

G4int SensitiveDetector::getHCID() const {
    return _hcids[0];
}

G4int SensitiveDetector::getHCID(G4int nHC) const {
    if (nHC > getNumberOfHitsCollections() + 1 || nHC < 0) {
        G4cerr << "The index " << nHC << " is not valid for SD " << this->GetName() << "." << G4endl;
        G4Exception("", "", FatalException, "Invalid index.");
    }
    return _hcids[nHC];
}

bool SensitiveDetector::isValidVolume(G4LogicalVolume* lv) {
    return lv != 0;
}

const std::string& SensitiveDetector::getHCName() const {
    return collectionName[0];
}

const std::string& SensitiveDetector::getHCName(G4int nHC) const {
    return collectionName[nHC];
}

void SensitiveDetector::setVerbose(unsigned int v) {
    _verbose = v;
}

unsigned int SensitiveDetector::getVerbose() const {
    return _verbose;
}

G4double SensitiveDetector::getEnergyCut() {
    return _ecut;
}

void SensitiveDetector::setEcut(G4double ecut) {
    _ecut = ecut;
}

void SensitiveDetector::setIdSpec(IdSpec* idspec) {
    _idspec = idspec;
}

IdSpec* SensitiveDetector::getIdSpec() const {
    return _idspec;
}

bool SensitiveDetector::hasIdSpec() const {
    return _idspec != 0;
}

void SensitiveDetector::setEndcapFlag(bool ec) {
    _endcap = ec;
}

bool SensitiveDetector::getEndcapFlag() {
    return _endcap;
}

int SensitiveDetector::getNumberOfHitsCollections() const {
    return _hcids.size();
}

void SensitiveDetector::setHCID(G4int hcid) {
    _hcids[0] = hcid;
}

void SensitiveDetector::setHCID(G4int hcid, G4int nHC) {
    if (nHC > getNumberOfHitsCollections() + 1 || nHC < 0) {
        G4cerr << this->GetName() << "setHCID Nr of HC" << nHC << "not valid" << G4endl;
        G4Exception("", "", FatalException, "Bad HC index.");
    }
    _hcids[nHC] = hcid;
}

void SensitiveDetector::addHitProcessor(HitProcessor* processor) {
    _hitProcessors.push_back(processor);
}

SensitiveDetector::HitProcessors SensitiveDetector::getHitProcessors() {
    return _hitProcessors;
}

void SensitiveDetector::addHitProcessors(std::vector<HitProcessor*> processors) {
    for (HitProcessors::iterator it = processors.begin(); it != processors.end(); it++) {
        _hitProcessors.push_back(*it);
    }
}
