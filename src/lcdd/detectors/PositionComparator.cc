#include "lcdd/detectors/PositionComparator.hh"

PositionComparator::PositionComparator() {
}

PositionComparator::~PositionComparator() {
}

bool PositionComparator::compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const {
    return (hit1.getPosition() == hit2.getPosition());
}

