// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/schema/HitsCollectionType.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/HitsCollectionType.hh"

HitsCollectionType::HitsCollectionType() {
}

HitsCollectionType::~HitsCollectionType() {
}

void HitsCollectionType::set_name(const std::string& s) {
    _name = s;
}

const std::string& HitsCollectionType::get_name() const {
    return _name;
}
