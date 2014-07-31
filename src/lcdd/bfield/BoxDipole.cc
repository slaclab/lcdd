#include "lcdd/bfield/BoxDipole.hh"

BoxDipole::~BoxDipole() {
}

BoxDipole::BoxDipole(double x, double y, double z, double dx, double dy, double dz, double bx, double by, double bz) :
        _x(x), _y(y), _z(z), _dx(dx), _dy(dy), _dz(dz), _bx(bx), _by(by), _bz(bz) {
    _maxx = x + dx;
    _maxy = y + dy;
    _maxz = z + dz;

    _minx = x - dx;
    _miny = y - dy;
    _minz = z - dz;
}

void BoxDipole::GetFieldValue(const double point[3], double* bfield) const {
    if (point[0] < _minx || point[0] > _maxx)
        return;
    if (point[1] < _miny || point[1] > _maxy)
        return;
    if (point[2] < _minz || point[2] > _maxz)
        return;

    bfield[0] += _bx;
    bfield[1] += _by;
    bfield[2] += _bz;

    //std::cout << point[0] << ", " << point[1] << ", " << point[2] << " --> " << bfield[0] << ", " << bfield[1] << ", " << bfield[2] << std::endl;
}
