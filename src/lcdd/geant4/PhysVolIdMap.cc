// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/geant4/PhysVolIdMap.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/geant4/PhysVolIdMap.hh"

PhysVolIdMap::PhysVolIdMap() {
}

PhysVolIdMap::~PhysVolIdMap() {
}

void PhysVolIdMap::addPhysVolId(G4VPhysicalVolume* pv, PhysVolId id) {
    if (!hasPhysVolIds(pv)) {
        createPhysVolIds(pv);
    }

    PhysVolId::PhysVolIds& idvec = getPhysVolIds(pv);
    idvec.push_back(id);
}

void PhysVolIdMap::createPhysVolIds(G4VPhysicalVolume* pv) {
    PhysVolId::PhysVolIds pvid;
    (*this)[pv] = pvid;
}

bool PhysVolIdMap::hasPhysVolIds(G4VPhysicalVolume* pv) const {
    return (this->find(pv) != this->end());
}

PhysVolId::PhysVolIds& PhysVolIdMap::getPhysVolIds(G4VPhysicalVolume* pv) {
    // create an empty one if not exists
    if (!hasPhysVolIds(pv)) {
        createPhysVolIds(pv);
    }

    // return ptr to vec
    return (*this)[pv];
}
