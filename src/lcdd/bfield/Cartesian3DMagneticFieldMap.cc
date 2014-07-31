//
// Original PurgMagTabulatedField3D code developed by:
//  S.Larsson and J. Generowicz.
//

#include "lcdd/bfield/Cartesian3DMagneticFieldMap.hh"

// STL
#include <fstream>
#include <iostream>
#include <cmath>

// Geant4
#include "globals.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

Cartesian3DMagneticFieldMap::Cartesian3DMagneticFieldMap(const char* filename, double xOffset, double yOffset, double zOffset) :
        _xOffset(xOffset), _yOffset(yOffset), _zOffset(zOffset), _invertX(false), _invertY(false), _invertZ(false) {
    G4cout << "-----------------------------------------------------------" << G4endl;
    G4cout << "    Magnetic field" << G4endl;	
    G4cout << "-----------------------------------------------------------" << G4endl << G4endl;

    G4cout << "Reading the field grid from " << filename << " ... " << endl;
    G4cout << "  Offsets: " << xOffset << " " << yOffset << " " << zOffset << G4endl;
    ifstream file(filename); // Open the file for reading.

    // Ignore first blank line
    char buffer[256];
    file.getline(buffer, 256);

    // Read table dimensions 
    file >> _nx >> _ny >> _nz; // Note dodgy order

    G4cout << "  Number of values: " << _nx << " " << _ny << " " << _nz << G4endl;

    // Set up storage space for table
    _xField.resize(_nx);
    _yField.resize(_nx);
    _zField.resize(_nx);
    int ix, iy, iz;
    for (ix = 0; ix < _nx; ix++) {
        _xField[ix].resize(_ny);
        _yField[ix].resize(_ny);
        _zField[ix].resize(_ny);
        for (iy = 0; iy < _ny; iy++) {
            _xField[ix][iy].resize(_nz);
            _yField[ix][iy].resize(_nz);
            _zField[ix][iy].resize(_nz);
        }
    }

    // Ignore other header information    
    // The first line whose second character is '0' is considered to
    // be the last line of the header.
    do {
        file.getline(buffer, 256);
    } while (buffer[1] != '0');

    // Read in the data
    double xval, yval, zval, bx, by, bz;
    for (ix = 0; ix < _nx; ix++) {
        for (iy = 0; iy < _ny; iy++) {
            for (iz = 0; iz < _nz; iz++) {
                file >> xval >> yval >> zval >> bx >> by >> bz;
                if (ix == 0 && iy == 0 && iz == 0) {
                    _minx = xval;
                    _miny = yval;
                    _minz = zval;
                }
                _xField[ix][iy][iz] = bx;
                _yField[ix][iy][iz] = by;
                _zField[ix][iy][iz] = bz;
            }
        }
    }
    file.close();

    _maxx = xval;
    _maxy = yval;
    _maxz = zval;

    G4cout << "  ... done reading " << G4endl << G4endl;
    G4cout << "Read values of field from file " << filename << G4endl;
    G4cout << "  Assumed the order: x, y, z, Bx, By, Bz" << G4endl;
    G4cout << "  Min values: " << _minx << " " << _miny << " " << _minz << " mm " << G4endl;
    G4cout << "  Max values: " << _maxx << " " << _maxy << " " << _maxz << " mm " << G4endl;
    G4cout << "  Field offsets: " << _xOffset << " " << _yOffset << " " << _zOffset << " mm " << G4endl << G4endl;

    // Should really check that the limits are not the wrong way around.
    if (_maxx < _minx) {
        swap(_maxx, _minx);
        _invertX = true;
    }
    if (_maxy < _miny) {
        swap(_maxy, _miny);
        _invertY = true;
    }
    if (_maxz < _minz) {
        swap(_maxz, _minz);
        _invertZ = true;
    }

    G4cout << "After reordering if necessary" << G4endl;
    G4cout << "  Min values: " << _minx << " " << _miny << " " << _minz << " mm " << G4endl;
    G4cout << "  Max values: " << _maxx << " " << _maxy << " " << _maxz << " mm " << G4endl;;

    _dx = _maxx - _minx;
    _dy = _maxy - _miny;
    _dz = _maxz - _minz;

    G4cout << "  Range of values: " << _dx << " " << _dy << " " << _dz << " mm" << G4endl << G4endl;
    G4cout << "Done loading field map" << G4endl << G4endl;
    G4cout  << "-----------------------------------------------------------" << G4endl << G4endl;
}

void Cartesian3DMagneticFieldMap::GetFieldValue(const double point[4], double *Bfield) const {

    double x = point[0] - _xOffset;
    double y = point[1] - _yOffset;
    double z = point[2] - _zOffset;

    // Check that the point is within the defined region 
    if (x >= _minx && x <= _maxx && y >= _miny && y <= _maxy && z >= _minz && z <= _maxz) {

        // Position of given point within region, normalized to the range
        // [0,1]
        double xfraction = (x - _minx) / _dx;
        double yfraction = (y - _miny) / _dy;
        double zfraction = (z - _minz) / _dz;

        if (_invertX) {
            xfraction = 1 - xfraction;
        }
        if (_invertY) {
            yfraction = 1 - yfraction;
        }
        if (_invertZ) {
            zfraction = 1 - zfraction;
        }

        // Need addresses of these to pass to modf below.
        // modf uses its second argument as an OUTPUT argument.
        double xdindex, ydindex, zdindex;

        // Position of the point within the cuboid defined by the
        // nearest surrounding tabulated points
        double xlocal = (std::modf(xfraction * (_nx - 1), &xdindex));
        double ylocal = (std::modf(yfraction * (_ny - 1), &ydindex));
        double zlocal = (std::modf(zfraction * (_nz - 1), &zdindex));

        // The indices of the nearest tabulated point whose coordinates
        // are all less than those of the given point
        int xindex = static_cast<int>(xdindex);
        int yindex = static_cast<int>(ydindex);
        int zindex = static_cast<int>(zdindex);

#ifdef DEBUG_INTERPOLATING_FIELD
        G4cout << "Local x,y,z: " << xlocal << " " << ylocal << " " << zlocal << G4endl;
        G4cout << "Index x,y,z: " << xindex << " " << yindex << " " << zindex << G4endl;
        double valx0z0, mulx0z0, valx1z0, mulx1z0;
        double valx0z1, mulx0z1, valx1z1, mulx1z1;
        valx0z0= table[xindex ][0][zindex]; mulx0z0= (1-xlocal) * (1-zlocal);
        valx1z0= table[xindex+1][0][zindex]; mulx1z0= xlocal * (1-zlocal);
        valx0z1= table[xindex ][0][zindex+1]; mulx0z1= (1-xlocal) * zlocal;
        valx1z1= table[xindex+1][0][zindex+1]; mulx1z1= xlocal * zlocal;
#endif

        // Full 3-dimensional version
        Bfield[0] = _xField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal)
                + _xField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal
                + _xField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal)
                + _xField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal
                + _xField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal)
                + _xField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal
                + _xField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal)
                + _xField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
        Bfield[1] = _yField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal)
                + _yField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal
                + _yField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal)
                + _yField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal
                + _yField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal)
                + _yField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal
                + _yField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal)
                + _yField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;
        Bfield[2] = _zField[xindex][yindex][zindex] * (1 - xlocal) * (1 - ylocal) * (1 - zlocal)
                + _zField[xindex][yindex][zindex + 1] * (1 - xlocal) * (1 - ylocal) * zlocal
                + _zField[xindex][yindex + 1][zindex] * (1 - xlocal) * ylocal * (1 - zlocal)
                + _zField[xindex][yindex + 1][zindex + 1] * (1 - xlocal) * ylocal * zlocal
                + _zField[xindex + 1][yindex][zindex] * xlocal * (1 - ylocal) * (1 - zlocal)
                + _zField[xindex + 1][yindex][zindex + 1] * xlocal * (1 - ylocal) * zlocal
                + _zField[xindex + 1][yindex + 1][zindex] * xlocal * ylocal * (1 - zlocal)
                + _zField[xindex + 1][yindex + 1][zindex + 1] * xlocal * ylocal * zlocal;

    } else {
        Bfield[0] = 0.0;
        Bfield[1] = 0.0;
        Bfield[2] = 0.0;
    }
}

/*
 int main()
 {
 Cartesian3DMagneticFieldMap field("C:/work/magfield/magfield3DMap/ThreeDFieldMap.dat", 0.,0.,0.);
 double pos[4];
 pos[0]=0.;
 pos[1]=0.;
 pos[2]=0.;
 pos[3]=0.;
 double B[3];

 for(double x=-0.05; x<=0.05; x+=.005)
 {
 for(double y=-0.05; y<=0.17; y+=.005)
 {
 for(double z=-0.26; z<=0.1; z+=.05)
 {
 pos[0]=x;
 pos[1] =y;
 pos[2] = z;
 field.GetFieldValue(pos, B);
 //G4cout << pos[0] << " " << pos[1] << " " << pos[2] << " " << B[0] << " " << B[1] << " " << B[2] << endl;
 }
 }
 }

 pos[0]=-0.01;
 pos[1]=0.038;
 pos[2]=-0.02;
 field.GetFieldValue(pos, B);
 //G4cout << pos[0] << " " << pos[1] << " " << pos[2] << " " << B[0] << " " << B[1] << " " << B[2] << endl;
 return 0;
 }
 */
