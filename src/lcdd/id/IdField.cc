#include "lcdd/id/IdField.hh"

IdField::IdField() {
}

IdField::~IdField() {
}

IdField::IdField(const std::string& label, SizeType start, SizeType length, bool isSigned) :
        _label(label), _start(start), _length(length), _isSigned(isSigned) {
}

void IdField::setLabel(const std::string& l) {
    _label = l;
}

void IdField::setStart(SizeType st) {
    _start = st;
}

void IdField::setLength(SizeType st) {
    _length = st;
}

void IdField::setSigned(bool s) {
    _isSigned = s;
}

const std::string& IdField::getLabel() {
    return _label;
}

IdField::SizeType IdField::getStart() {
    return _start;
}

IdField::SizeType IdField::getLength() {
    return _length;
}

bool IdField::getSigned() {
    return _isSigned;
}
