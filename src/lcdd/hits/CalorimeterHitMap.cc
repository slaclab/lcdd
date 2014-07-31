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

int CalorimeterHitMap::size() {
    return _map.size();
}
