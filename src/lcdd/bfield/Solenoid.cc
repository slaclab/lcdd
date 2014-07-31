#include "lcdd/bfield/Solenoid.hh"

// Geant4
#include "globals.hh"

Solenoid::Solenoid() :
        _innerField(0), _outerField(0), _innerR(0), _outerR(0), _innerZ(0), _outerZ(0) {
}

Solenoid::~Solenoid() {
}

/**
 * Apply simple solenoid magnetic field to the given Point.
 * @todo Use the inner and outer Z values.
 */
void Solenoid::GetFieldValue(const double Point[3], double* Bfield) const {
    double this_radius = sqrt(Point[0] * Point[0] + Point[1] * Point[1]);
    if (this_radius < _innerR) {
        Bfield[2] += _innerField;
    } else if (this_radius < _outerR) {
        Bfield[2] += _outerField;
    }
    return;
}

void Solenoid::printOut(std::ostream& os) {
    os << "innerField <" << _innerField << ">" << std::endl;
    os << "outerField <" << _outerField << ">" << std::endl;
    os << "outerR <" << _outerR << ">" << std::endl;
    os << "innerZ <" << _innerZ << ">" << std::endl;
    os << "outerZ <" << _outerZ << ">" << std::endl;
    os << std::endl;
}

void Solenoid::setInnerField(double d) {
    _innerField = d;
}

void Solenoid::setOuterField(double d) {
    _outerField = d;
}

void Solenoid::setInnerR(double d) {
    _innerR = d;
}

void Solenoid::setOuterR(double d) {
    _outerR = d;
}

void Solenoid::setInnerZ(double d) {
    _innerZ = d;
}

void Solenoid::setOuterZ(double d) {
    _outerZ = d;
}

double Solenoid::getInnerField() const {
    return _innerField;
}

double Solenoid::getOuterField() const {
    return _outerField;
}

double Solenoid::getInnerR() const {
    return _innerR;
}

double Solenoid::getOuterR() const {
    return _outerR;
}

double Solenoid::getInnerZ() const {
    return _innerZ;
}

double Solenoid::getOuterZ() const {
    return _outerZ;
}
