// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/schema/hits_collection.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

#include "lcdd/schema/hits_collection.hh"

hits_collection::hits_collection() {
}

hits_collection::~hits_collection() {
}

SAXObject::Type hits_collection::type() {
    return SAXObject::element;
}

