// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/id/IdComparator.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/id/IdComparator.hh"

IdComparator::IdComparator() {
}

IdComparator::~IdComparator() {
}

bool IdComparator::compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const {
    return (hit1.getId64bit() == hit2.getId64bit());
}
