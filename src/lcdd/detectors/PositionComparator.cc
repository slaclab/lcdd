// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/PositionComparator.cc,v 1.3 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/PositionComparator.hh"

PositionComparator::PositionComparator() {
}

PositionComparator::~PositionComparator() {
}

bool PositionComparator::compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const {
    return (hit1.getPosition() == hit2.getPosition());
}

