#ifndef LCDD_BFIELD_CARTESIAN3DMAGNETICFIELDMAP_HH_
#define LCDD_BFIELD_CARTESIAN3DMAGNETICFIELDMAP_HH_ 1

// Geant4
#include "G4MagneticField.hh"

// STL
#include <vector>
using std::vector;

/**
 * @brief
 * A 3D B-field map defined as a grid of points with associated B-field values.
 *
 * @note
 * Values are interpolated to obtain B-field information at points in between.
 *
 * @details
 * The header format of the input data file is as follows:
 *
 * 1) Blank line
 *
 * 2) int int int
 *
 * Number of X, Y, and Z grid points (N_x, N_y, N_z)
 *
 * 3-8) int String
 *
 * A description of fields in the lines of the map.  In our case it is literally:
 *
 * 1 X
 * 2 Y
 * 3 Z
 * 4 BX
 * 5 BY
 * 6 BZ
 *
 * 9) int String
 *
 * Header terminator
 *
 * 10+) float float float float float float
 *
 * N_x*N_y*N_z+9
 *
 * x y z B_x B_y B_z
 *
 * Original PurgMagTabulatedField3D code developed by: S.Larsson and J. Generowicz.
 *
 * @author Norman Graf
 */
class Cartesian3DMagneticFieldMap: public G4MagneticField {
private:

    // Storage space for the table
    vector<vector<vector<double> > > _xField;
    vector<vector<vector<double> > > _yField;
    vector<vector<vector<double> > > _zField;

    // The dimensions of the table
    int _nx, _ny, _nz;

    // The physical limits of the defined region
    double _minx, _maxx, _miny, _maxy, _minz, _maxz;

    // The physical extent of the defined region
    double _dx, _dy, _dz;

    // Offsets if field map is not in global coordinates
    double _xOffset;
    double _yOffset;
    double _zOffset;

    bool _invertX, _invertY, _invertZ;

public:

    /**
     * Class constructor.
     * @param[in] filename The name of the file defining the B-field grid.
     * @param[in] xOffset, yOffset, zOffset The offset of the grid's coordinate system.
     */
    Cartesian3DMagneticFieldMap(const char* filename, double xOffset, double yOffset, double zOffset);

    /**
     * Implementation of primary virtual method from G4MagneticField interface.
     * @param[in]  Point  The point in 3D space.
     * @param[out] Bfield The output B-field data at the point.
     */
    void GetFieldValue(const double Point[4], double* Bfield) const;
};

#endif
