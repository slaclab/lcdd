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

CalorimeterHit* CalorimeterHitMap::get(Id64bit::ValueType value) {
    return _map[value];
}

void CalorimeterHitMap::clear() {
    _map.clear();
}

int CalorimeterHitMap::size() {
    return _map.size();
}
