#include "lcdd/bfield/MagneticFieldOverlay.hh"

// STL
#include <iostream>

MagneticFieldOverlay::MagneticFieldOverlay() {
}

MagneticFieldOverlay::~MagneticFieldOverlay() {
}

void MagneticFieldOverlay::addMagneticField(G4MagneticField* field) {
    if (field != 0) {
        _fields.push_back(field);
    }
}

/**
 * Call GetFieldValue of all G4MagneticField objects registered with this MagneticFieldOverlay.
 */
void MagneticFieldOverlay::GetFieldValue(const double Point[3], double *Bfield) const {
    Bfield[0] = Bfield[1] = Bfield[2] = 0.;
    for (std::vector<G4MagneticField*>::const_iterator iter = _fields.begin(); iter != _fields.end(); iter++) {
        (*iter)->GetFieldValue(Point, Bfield);
    }
}
