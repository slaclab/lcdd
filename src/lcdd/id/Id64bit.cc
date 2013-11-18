// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/id/Id64bit.cc,v 1.3 2013-11-13 23:02:57 jeremy Exp $

#include "lcdd/id/Id64bit.hh"

#include <iostream>

Id64bit::Id64bit() :
        _value(0) {
    _ids[0] = 0;
    _ids[1] = 0;
    encode();
}

Id64bit::Id64bit(ElementType id0, ElementType id1) :
        _value(0) {
    _ids[0] = id0;
    _ids[1] = id1;
    encode();
}

Id64bit::Id64bit(const Id64bit &right) :
        _value(0) {
    _ids[0] = right._ids[0];
    _ids[1] = right._ids[1];
    encode();
}

Id64bit::~Id64bit() {
}

void Id64bit::setId0(ElementType id0) {
    _ids[0] = id0;
}

void Id64bit::setId1(ElementType id1) {
    _ids[1] = id1;
}

Id64bit::ElementType Id64bit::getId0() const {
    return _ids[0];
}

Id64bit::ElementType Id64bit::getId1() const {
    return _ids[1];
}

bool Id64bit::operator==(const Id64bit& right) const {
    return (_ids[0] == right._ids[0] && _ids[1] == right._ids[1]);
}

void Id64bit::encode() {
    // Encode the first 32 bits contained in id0.
    _value |= _ids[0];

    // Create value for second int in id1.
    ValueType id1 = _ids[1];

    // Encode id1 into second 32 bits.
    _value |= (id1 << 32);
}

Id64bit::ValueType Id64bit::getValue() const {
    return _value;
}
