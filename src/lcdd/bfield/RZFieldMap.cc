#include "lcdd/bfield/RZFieldMap.hh"

// Geant4
#include "globals.hh"

// STL
#include <cmath>

// Set this preprocessor symbol for lots of debugging output.
//#define FIELD_MAP_DEBUG 1

#ifdef FIELD_MAP_DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

RZFieldMap::RZFieldMap(int numBinsR, int numBinsZ, double gridSizeR, double gridSizeZ, std::vector<RZBData> fieldData) :
        _numBinsR(numBinsR), _numBinsZ(numBinsZ), _gridSizeR(gridSizeR), _gridSizeZ(gridSizeZ), _BrArray(0), _BzArray(0) {

#ifdef FIELD_MAP_DEBUG
    cout << "numBinsR=" << numBinsR << endl;
    cout << "numBinsZ=" << numBinsZ << endl;
    cout << "gridSizeR=" << gridSizeR << endl;
    cout << "gridSizeZ=" << gridSizeZ << endl;
#endif

    if (numBinsR < 2) {
        G4Exception("", "", FatalException, "numBinsR must be >= 2");
    }

    if (numBinsZ < 2) {
        G4Exception("", "", FatalException, "numBinsZ must be >= 2");
    }

    if (gridSizeR <= 0) {
        G4Exception("", "", FatalException, "gridSizeR must be >= 0");
    }

    if (gridSizeZ <= 0) {
        G4Exception("", "", FatalException, "gridSizeZ must be >= 0");
    }

    _maxR = (numBinsR - 1) * _gridSizeR;
    _maxZ = (numBinsZ - 1) * _gridSizeZ;

    initializeArrays();

    fillArrays(fieldData);
}

void RZFieldMap::initializeArrays() {
    // Make two 2D arrays of numBinsZ x numBinsR 
    _BrArray = new double*[_numBinsZ];
    _BzArray = new double*[_numBinsZ];

    for (int i = 0; i < _numBinsZ; i++) {
        _BrArray[i] = new double[_numBinsR];
        _BzArray[i] = new double[_numBinsR];
    }

    // Initialize arrays to all 0's.
    for (int i = 0; i < _numBinsZ; i++) {
        for (int j = 0; j < _numBinsR; j++) {
            _BrArray[i][j] = 0;
            _BzArray[i][j] = 0;
        }
    }
}

void RZFieldMap::fillArrays(std::vector<RZBData> fieldData) {
    for (std::vector<RZBData>::iterator iter = fieldData.begin(); iter != fieldData.end(); iter++) {
        RZBData rzb = *iter;

        int iz = (int) ((rzb.z() + 0.0001) / _gridSizeZ);
        int ir = (int) ((rzb.r() + 0.0001) / _gridSizeR);

        _BzArray[iz][ir] = rzb.Bz();
        _BrArray[iz][ir] = rzb.Br();

#ifdef FIELD_MAP_DEBUG
        cout << "ir iz = " << ir << " " << iz << endl;
        cout << "Br Bz = " << _BrArray[iz][ir] << " " << _BzArray[iz][ir] << endl;
        cout << endl;
#endif
    }
}

RZFieldMap::~RZFieldMap() {
    deleteArrays();
}

void RZFieldMap::deleteArrays() {
    for (int i = 0; i < _numBinsZ; i++) {
        delete[] _BrArray[i];
        delete[] _BzArray[i];
    }
    delete[] _BrArray;
    delete[] _BzArray;
}

/**
 * Compute B-field at given point using the arrays of Br and Bz field components.
 *
 * This function is based on Takashi's FORTRAN code:
 *
 * /afs/slac/www/accel/nlc/local/systems/beamdelivery/geant/SDNEW/solenoid.f
 *
 * via the RZBFieldProvider.cpp test code provided by Norman.
 *
 */
void RZFieldMap::GetFieldValue(const double Point[3], double *Bfield) const {
#ifdef FIELD_MAP_DEBUG
    cout << "Point = " << Point[0] << " " << Point[1] << " " << Point[2] << endl;
#endif

    double r = sqrt((Point[0] * Point[0]) + (Point[1] * Point[1]));
    double z = Point[2];

    double hz = 0;
    double hr = 0;

    // Check for z or r out of range.
    if (fabs(z) >= _maxZ || r >= _maxR) {
#ifdef FIELD_MAP_DEBUG
        cout << "OUT OF RANGE: z r = " << fabs(z) << " " << r << endl;
        cout << "MAX: maxZ maxR " << _maxZ << " " << _maxR << endl;
#endif
        return;
    }

    // Compute z bin.
    int iz = (int) ((fabs(z) + 0.001) / _gridSizeZ);

    // Compute r bin.
    int ir = (int) ((r + 0.001) / _gridSizeR);

    // Adjust for iz out of range.
//   int izfar = 0;
//   if( iz >= m_numBinsZ-1 ) {
//     izfar = 1;
//     iz = m_numBinsZ - 1;
//   }

// Check for iz < 0.
    if (iz < 0) {
#ifdef FIELD_MAP_DEBUG
        cout << "ERROR: iz < 0" << endl;
        cout << "iz=" << iz << endl;
        cout << "returning" << endl;
#endif
    }

// Check for Z overflow on iz+1.
    if (iz + 1 >= _numBinsZ) {
#ifdef FIELD_MAP_DEBUG
        cout << "ERROR: iz overflow" << endl;
        cout << "iz=" << iz << endl;
        cout << "returning" << endl;
#endif
        return;
    }

    // Check for R overflow on ir+1.
    if (ir + 1 >= _numBinsR) {
#ifdef FIELD_MAP_DEBUG
        cout << "ERROR: ir overflow" << endl;
        cout << "ir=" << ir << endl;
        cout << "returning" << endl;
#endif
        return;
    }

#ifdef FIELD_MAP_DEBUG
    cout << "dz " << _gridSizeZ << " dr " << _gridSizeR << endl;
    cout << "z " << z << " r " << r << endl;
    cout << "iz " << iz << " ir " << ir << endl;
#endif

    double bz0 = _BzArray[iz][ir];
    double br0 = _BrArray[iz][ir];

#ifdef FIELD_MAP_DEBUG
    cout << "bz0 " << bz0 << " br0 " << br0 << endl;
#endif

    double delz = 0.;
    double delr = 0.;

    double brdz = 0.;
    double brdr = 0.;

    if (r > 0.0) {
        delr = r - float(ir) * _gridSizeR;

#ifdef FIELD_MAP_DEBUG
        if ( iz+1 == _gridSizeZ-1 ) {
            cout << "WARNING: iz+1 == gridSizeZ-1" << endl;
        }

        if ( ir+1 == _gridSizeR-1 ) {
            cout << "WARNING: ir+1 == gridSizeR-1" << endl;
        }
#endif

#ifdef FIELD_MAP_DEBUG
        cout << "checking brarray access ..." << endl;
        cout << "iz+1=" << iz+1 << endl;
        cout << "ir=" << ir << endl;
        cout << _BrArray[iz+1][ir] << endl;
        cout << "m_BrArray[iz+1][ir] is ok" << endl;
        cout << "iz=" << iz << endl;
        cout << "ir+1=" << ir+1 << endl;
        cout << _BrArray[iz][ir+1] << endl;
        cout << "m_BrArray[iz][ir+1] is ok" << endl;
        cout << "done" << endl;
#endif

        brdz = (_BrArray[iz + 1][ir] - br0) / _gridSizeZ;
        brdr = (_BrArray[iz][ir + 1] - br0) / _gridSizeR;
#ifdef FIELD_MAP_DEBUG
        cout << "br= " << _BrArray[iz+1][ir] << " " << _BrArray[iz][ir+1] << endl;
#endif
    }

    delz = fabs(z) - float(iz) * _gridSizeZ;

#ifdef FIELD_MAP_DEBUG
    cout << " z " << z << " abs(z) " << fabs(z) << " iz " << iz << endl;
    cout << " float(iz-1) " << float(iz-1) << " dz " << _gridSizeZ << endl;
    cout << " delz " << delz << endl;
#endif

    double bzdz = (_BzArray[iz + 1][ir] - bz0) / _gridSizeZ;
    double bzdr = (_BzArray[iz][ir + 1] - bz0) / _gridSizeR;

#ifdef FIELD_MAP_DEBUG
    cout << "bz= " << _BzArray[iz+1][ir] << " " << _BzArray[iz][ir+1] << endl;
#endif

//   if(izfar==1) {
//     hz = bz0+bzdr*delr;
//     hr = br0+brdr*delr;
//   }
//   else {
    hz = bz0 + bzdz * delz + bzdr * delr;
    hr = br0 + brdz * delz + brdr * delr;
//   }

    if (z < 0.0)
        hr = -hr;

    double theta = atan2(Point[1], Point[0]);
    double hx = hr * cos(theta);
    double hy = hr * sin(theta);

    Bfield[0] += hx;
    Bfield[1] += hy;
    Bfield[2] += hz;

#ifdef FIELD_MAP_DEBUG
    cout << "Bfield XYZ = " << Bfield[0] << " " << Bfield[1] << " " << Bfield[2] << endl;
    cout << endl;
#endif
}
