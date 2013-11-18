// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/id/IdVec.cc,v 1.3 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/id/IdVec.hh"

IdVec::IdVec() {
}

IdVec::~IdVec() {
}

void IdVec::clear() {
    _fields.clear();
}

void IdVec::addFieldValue(ElementType et) {
    _fields.push_back(et);
}

IdVec::ElementType IdVec::getFieldValue(SizeType idx) const {
    return _fields.at(idx);
}

void IdVec::setFieldValue(SizeType idx, ElementType et) {
    _fields.insert(_fields.begin() + idx, et);
}

IdVec::ElementType IdVec::operator [](SizeType idx) const {
    return getFieldValue(idx);
}

IdVec::ElementVector::const_iterator IdVec::getFieldsBegin() const {
    return _fields.begin();
}

IdVec::ElementVector::const_iterator IdVec::getFieldsEnd() const {
    return _fields.end();
}

IdVec::SizeType IdVec::size() const {
    return _fields.size();
}
