#ifndef LCDD_BFIELD_BOXDIPOLE_HH
#define LCDD_BFIELD_BOXDIPOLE_HH 1

// Geant4
#include "G4MagneticField.hh"

/**
 * @brief This is a G4MagneticField implementation that assigns fixed B-field components to a box-like
 * region with a possible offset in world coordinates.
 */
class BoxDipole: public G4MagneticField {
public:

    /**
     * Class constructor.
     * @param[in] x, y, z    The global position of the box's center.
     * @param[in] dx, dy, dz The half lengths of the box.
     * @param[in] by, by, bz The B-field coordinates for the region.
     */
    BoxDipole(double x, double y, double z, double dx, double dy, double dz, double bx, double by, double bz);

    /**
     * Class destructor.
     */
    virtual ~BoxDipole();

    /**
     * Implementation of G4MagneticField class's primary method to get B-field at a point.
     * @param[in] point   The 3D point at which B-field components will be read.
     * @param[out] bfield The output B-field components at the point.
     */
    void GetFieldValue(const double point[3], double *bfield) const;

private:

    double _x;
    double _y;
    double _z;
    double _dx;
    double _dy;
    double _dz;
    double _bx;
    double _by;
    double _bz;

    double _maxx;
    double _maxy;
    double _maxz;
    double _minx;
    double _miny;
    double _minz;
};

#endif
