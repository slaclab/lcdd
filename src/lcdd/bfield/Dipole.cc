// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/bfield/Dipole.cc,v 1.4 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/bfield/Dipole.hh"

// STL
#include <iostream>
#include <cmath>

Dipole::Dipole() {
}

Dipole::~Dipole() {
}

/**
 * Apply polynomial fit of dipole field, with variable number of coefficients
 * read from the input XML file.
 */
void Dipole::GetFieldValue(const double Point[3], double* Bfield) const {
    //std::cout << "G4Dipole::GetFieldValue" << std::endl;

    //std::cout << "point = " << Point[0] << " " << Point[1] << " " << Point[2] << std::endl;
    //std::cout << "BEFORE --> bfield = " << Bfield[0] << " " << Bfield[1] << " " << Bfield[2] << std::endl;

    double bx = 0;
    double z = Point[2];
    double r = sqrt(Point[0] * Point[0] + Point[1] * Point[1]);

    // Check if z coordinate is within dipole z bounds.
    if (z > _zmin && z < _zmax && r < _rmax) {

        // Convert to absolute value z and apply specified length unit.
        double zc = fabs(z) / _lunit;

        //std::cout << "zc = " << zc << std::endl;

        // Apply all coefficients to this z coordinate.
        for (size_t i = 0; i < _coeffs.size(); ++i) {
            bx += _coeffs[i] * pow(zc, i);
        }

        // Convert to specified field unit.
        bx *= _funit;

        // Flip sign for negative z.
        if (z < 0) {
            bx = -bx;
        }

        // Add Bx to the input Bfield.
        Bfield[0] += bx;
    }

    //std::cout << "AFTER --> bfield = " << Bfield[0] << " " << Bfield[1] << " " << Bfield[2] << std::endl << std::endl;
    //std::cout << Point[2] << " " << Bfield[0] << std::endl;

    return;
}

void Dipole::setZMax(double zmax) {
    _zmax = zmax;
}

double Dipole::getZMax() {
    return _zmax;
}

void Dipole::setZMin(double zmin) {
    _zmin = zmin;
}

double Dipole::getZMin() {
    return _zmin;
}

void Dipole::setRMax(double rmax) {
    _rmax = rmax;
}

double Dipole::getRMax() {
    return _rmax;
}

void Dipole::addCoeff(double coeff) {
    _coeffs.push_back(coeff);
}

const std::vector<double>& Dipole::getCoeffs() {
    return _coeffs;
}

void Dipole::setFieldUnit(double unit) {
    _funit = unit;
}

double Dipole::getFieldUnit() {
    return _funit;
}

void Dipole::setLengthUnit(double unit) {
    _lunit = unit;
}

double Dipole::getLengthUnit() {
    return _lunit;
}
