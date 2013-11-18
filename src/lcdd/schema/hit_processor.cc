// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/schema/hit_processor.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/hit_processor.hh"

hit_processor::hit_processor() {
}

hit_processor::~hit_processor() {
}

SAXObject::Type hit_processor::type() {
    return SAXObject::element;
}

