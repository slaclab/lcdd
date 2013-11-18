// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/core/LCDDProcessor.cc,v 1.4 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/bfield/FieldManager.hh"
#include "lcdd/bfield/MagneticFieldOverlay.hh"

// Geant4
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCtable.hh"

LCDDProcessor* LCDDProcessor::_instance = 0;

LCDDProcessor::LCDDProcessor() :
        _header(0) {
}

LCDDProcessor::~LCDDProcessor() {
    if (_header != 0) {
        delete _header;
    }
}

LCDDProcessor* LCDDProcessor::instance() {
    if (_instance == 0) {
        _instance = new LCDDProcessor;
    }

    return _instance;
}

void LCDDProcessor::addSensitiveDetector(std::string& name, SensitiveDetector* sd) {
    //std::cout << "adding SD: " << name << std::endl;
    _sensitiveDetectors[name] = sd;
}

SensitiveDetector* LCDDProcessor::getSensitiveDetector(const std::string& name) {
    return _sensitiveDetectors[name];
}

SensitiveDetector* LCDDProcessor::getSensitiveDetector(const char* name) {
    std::string key = name;
    return getSensitiveDetector(key);
}

LCDDProcessor::SensitiveDetectors::const_iterator LCDDProcessor::getSensitiveDetectorsBegin() {
    return _sensitiveDetectors.begin();
}

LCDDProcessor::SensitiveDetectors::const_iterator LCDDProcessor::getSensitiveDetectorsEnd() {
    return _sensitiveDetectors.end();
}

void LCDDProcessor::addMagneticField(std::string& name, G4MagneticField* mag) {
    _magneticFields[name] = mag;
}

void LCDDProcessor::addGlobalField(G4MagneticField* mag) {
    FieldManager::instance()->addGlobalField(mag);
}

G4MagneticField* LCDDProcessor::getMagneticField(const std::string& name) {
    return _magneticFields[name];
}

G4MagneticField* LCDDProcessor::getMagneticField(const char* name) {
    std::string key = name;
    return getMagneticField(key);
}

LCDDProcessor::MagneticFields::const_iterator LCDDProcessor::getMagneticFieldsBegin() {
    return _magneticFields.begin();
}

LCDDProcessor::MagneticFields::const_iterator LCDDProcessor::getMagneticFieldsEnd() {
    return _magneticFields.end();
}

void LCDDProcessor::addRegion(std::string& name, G4Region* reg) {
    _regions[name] = reg;
}

G4Region* LCDDProcessor::getRegion(const std::string& name) {
    return _regions[name];
}

G4Region* LCDDProcessor::getRegion(const char* name) {
    std::string key = name;
    return getRegion(name);
}

LCDDProcessor::Regions::const_iterator LCDDProcessor::getRegionsBegin() {
    return _regions.begin();
}

LCDDProcessor::Regions::const_iterator LCDDProcessor::getRegionsEnd() {
    return _regions.end();
}

void LCDDProcessor::addVisAttributes(std::string& name, G4VisAttributes* vis) {
    _visAttributes[name] = vis;
}

G4VisAttributes* LCDDProcessor::getVisAttributes(const std::string& name) {
    return _visAttributes[name];
}

G4VisAttributes* LCDDProcessor::getVisAttributes(const char* name) {
    std::string key = name;
    return getVisAttributes(key);
}

LCDDProcessor::VisAttributes::const_iterator LCDDProcessor::getVisAttributesBegin() {
    return _visAttributes.begin();
}

LCDDProcessor::VisAttributes::const_iterator LCDDProcessor::getVisAttributesEnd() {
    return _visAttributes.end();
}

void LCDDProcessor::addLimitSet(std::string& name, PhysicsLimitSet* lim) {
    _limitSets[name] = lim;
}

PhysicsLimitSet* LCDDProcessor::getLimitSet(const std::string& name) {
    return _limitSets[name];
}

PhysicsLimitSet* LCDDProcessor::getLimitSet(const char* name) {
    std::string key = name;
    return getLimitSet(key);
}

LCDDProcessor::LimitSets::const_iterator LCDDProcessor::getLimitSetsBegin() {
    return _limitSets.begin();
}

LCDDProcessor::LimitSets::const_iterator LCDDProcessor::getLimitSetsEnd() {
    return _limitSets.end();
}

const LCDDHeaderRecord* LCDDProcessor::getHeader() const {
    return _header;
}

void LCDDProcessor::setHeader(LCDDHeaderRecord* h) {
    assert(h);
    _header = h;
}

std::string LCDDProcessor::getDetectorName() const {
    std::string detTag;
    if (_header == 0) {
        detTag = "UNKNOWN";
    } else {
        detTag = _header->getDetectorName();
    }
    return detTag;
}

const LCDDProcessor::VisAttributes* LCDDProcessor::getVisAttributesStore() const {
    return &_visAttributes;
}

const LCDDProcessor::SensitiveDetectors* LCDDProcessor::getSensitiveDetectorStore() const {
    return &_sensitiveDetectors;
}

const LCDDProcessor::MagneticFields* LCDDProcessor::getMagneticFieldStore() const {
    return &_magneticFields;
}

const LCDDProcessor::Regions* LCDDProcessor::getRegionStore() const {
    return &_regions;
}

const LCDDProcessor::LimitSets* LCDDProcessor::getLimitSetStore() const {
    return &_limitSets;
}
