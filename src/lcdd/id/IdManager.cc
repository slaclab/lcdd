// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/id/IdManager.cc,v 1.6 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/id/IdManager.hh"

// Geant4
#include "G4LogicalVolume.hh"

IdManager* IdManager::_instance = 0;

IdManager::IdManager() {
}

IdManager::~IdManager() {
}

IdManager* IdManager::instance() {
    if (_instance == 0) {
        _instance = new IdManager;
    }

    return _instance;
}

void IdManager::addIdSpec(const std::string& name, IdSpec* spec) {
    _idSpecs[name] = spec;
}

IdSpec* IdManager::getIdSpec(const char* name) {
    std::string key = name;
    return getIdSpec(key);
}

IdSpec* IdManager::getIdSpec(const std::string& name) {
    return _idSpecs[name];
}

IdManager::IdSpecs::const_iterator IdManager::getIdSpecsBegin() {
    return _idSpecs.begin();
}

IdManager::IdSpecs::const_iterator IdManager::getIdSpecsEnd() {
    return _idSpecs.end();
}

void IdManager::addPhysVolId(G4LogicalVolume* lvMom, int childIdx, PhysVolId childId) {
    // DEBUG
    //std::cout << std::endl << "assigning physvolid..." << std::endl;
    //std::cout << "lvMom <" << lvMom->GetName() << ">" << std::endl;
    //std::cout << "childIdx <" << childIdx << ">" << std::endl;
    //std::cout << "childId field: " << childId.getFieldName() << std::endl;
    //std::cout << "childId <" << childId.getValue() << ">" << std::endl;
    //

    G4VPhysicalVolume* dau = lvMom->GetDaughter(childIdx);

    if (dau) {

        //std::cout << "found daughter <" << dau->GetName() << ">" << std::endl;
        //std::cout << "dau ptr <" << dau << ">" << std::endl;

        _physVolIdMap.addPhysVolId(dau, childId);
    } else {
        std::cerr << "IdManager::assignPhysVolId() - childIdx <" << childIdx << "> does not exist!" << std::endl;
    }

    //std::cout << std::endl;
}

void IdManager::printIds(std::ostream& os, const IdVec& ids) {
    os << "id stack:";

    for (std::vector<int>::const_iterator iter = ids.getFieldsBegin(); iter != ids.getFieldsEnd(); iter++) {
        os << " " << *iter;
    }

    os << std::endl;
}

bool IdManager::hasPhysVolIds(G4VPhysicalVolume* pv) const {
    return _physVolIdMap.hasPhysVolIds(pv);
}

const PhysVolIdMap& IdManager::getPhysVolIdMap() const {
    return _physVolIdMap;
}

PhysVolId::PhysVolIds& IdManager::getPhysVolIds(G4VPhysicalVolume* pv) {
    return _physVolIdMap.getPhysVolIds(pv);
}

const IdManager::IdSpecs* IdManager::getIdSpecStore() {
    return &_idSpecs;
}
