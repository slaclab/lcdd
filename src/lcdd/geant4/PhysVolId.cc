#include "lcdd/geant4/PhysVolId.hh"

PhysVolId::PhysVolId(ValueType val, std::string fld) :
        _value(val), _fieldName(fld) {
}

PhysVolId::~PhysVolId() {
}

PhysVolId::ValueType PhysVolId::getValue() const {
    return _value;
}

const std::string& PhysVolId::getFieldName() const {
    return _fieldName;
}

bool PhysVolId::operator==(const PhysVolId& right) {
    return (_value == right._value);
}

bool PhysVolId::operator==(ValueType vt) {
    return (_value == vt);
}
