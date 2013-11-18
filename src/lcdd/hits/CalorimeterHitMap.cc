// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/hits/CalorimeterHitMap.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

#include "lcdd/hits/CalorimeterHitMap.hh"

CalorimeterHitMap::CalorimeterHitMap() {
}

CalorimeterHitMap::~CalorimeterHitMap() {
    _map.clear();
}

void CalorimeterHitMap::add(CalorimeterHit* hit) {
    _map[hit->getId64bit().getValue()] = hit;
}

CalorimeterHit* CalorimeterHitMap::get(const Id64bit& id) {
    return _map[id.getValue()];
}

void CalorimeterHitMap::clear() {
    _map.clear();
}
