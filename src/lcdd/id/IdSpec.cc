// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/id/IdSpec.cc,v 1.5 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/id/IdSpec.hh"

// STL
#include <sstream>

using namespace std;

IdSpec::IdSpec() {
}

IdSpec::~IdSpec() {
    deleteIdFields();
}

void IdSpec::setName(const std::string& n) {
    _name = n;
}

void IdSpec::setBitLength(SizeType st) {
    _bitLength = st;
}

IdSpec::SizeType IdSpec::getBitLength() const {
    return _bitLength;
}

const std::string& IdSpec::getName() const {
    return _name;
}

IdSpec::SizeType IdSpec::getNumFields() const {
    return _idFields.size();
}

void IdSpec::addIdField(IdField* f) {
    _idFields.push_back(f);
}

IdField* IdSpec::getIdField(const std::string& n) const {
    IdField* f = 0;
    for (IdFields::const_iterator iter = IdFieldsBegin(); iter != IdFieldsEnd(); iter++) {
        if (n == (*iter)->getLabel()) {
            f = *iter;
            break;
        }
    }
    return f;
}

IdField* IdSpec::getIdField(SizeType st) const {
    return _idFields[st];
}

const IdSpec::IdFields& IdSpec::getIdFields() const {
    return _idFields;
}

IdSpec::IdFields::const_iterator IdSpec::IdFieldsBegin() const {
    return _idFields.begin();
}

IdSpec::IdFields::const_iterator IdSpec::IdFieldsEnd() const {
    return _idFields.end();
}

void IdSpec::clear() {
    _idFields.clear();
}

void IdSpec::deleteIdFields() {
    if (_idFields.size() > 0) {
        for (IdFields::iterator iter = _idFields.begin(); iter != _idFields.end(); iter++) {
            delete *iter;
        }
        _idFields.clear();
    }
}

void IdSpec::printOut(std::ostream& os) const {
    os << std::endl;

    os << "IdSpec: " << _name << std::endl;
    os << "bitLength: " << _bitLength << std::endl;

    static const int def_width = 15;

    os.width(def_width);
    os << left << "label";

    os.width(def_width);
    os << left << "start";

    os.width(def_width);
    os << left << "end";

    os.width(def_width);
    os << left << "size";

    os.width(def_width);
    os << left << "signed";

    os << std::endl;

    os.fill('-');
    os.width(66);
    os << left << "-" << std::endl;

    os.fill(' ');

    for (IdFields::const_iterator iter = IdFieldsBegin(); iter != IdFieldsEnd(); iter++) {

        IdField* f = *iter;

        os.width(def_width);
        os << left << f->getLabel();

        os.width(def_width);
        os << left << f->getStart();

        os.width(def_width);
        os << left << f->getStart() + f->getLength() - 1;

        os.width(def_width);
        os << left << f->getLength();

        os.width(def_width);
        os << left << f->getSigned();

        os.width(def_width);
        os << left << std::endl;
    }

    os << std::endl;
}

std::string IdSpec::getFieldDescription() {
    std::stringstream enc;

    // Loop over the fields in the IdSpec.
    for (IdSpec::IdFields::const_iterator it = this->IdFieldsBegin(); it != this->IdFieldsEnd(); it++) {

        // Get the IdField.
        IdField* field = (*it);

        // Encode the field information into the LCIO / compact format.
        enc << field->getLabel() << ":" << field->getStart() << ":";
        if (field->getSigned()) {
            enc << "-";
        }
        enc << field->getLength() << ",";
    }

    // Return the id description string, eliminating last comma.
    return enc.str().substr(0, enc.str().length() - 1);
}
