#include "lcdd/id/IdComparator.hh"

IdComparator::IdComparator() {
}

IdComparator::~IdComparator() {
}

bool IdComparator::compare(const CalorimeterHit& hit1, const CalorimeterHit& hit2) const {
    return (hit1.getId64bit() == hit2.getId64bit());
}
