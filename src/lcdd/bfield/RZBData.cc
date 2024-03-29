#include "lcdd/bfield/RZBData.hh"

RZBData::RZBData(double r, double z, double Br, double Bz) :
        _r(r), _z(z), _Br(Br), _Bz(Bz) {
}

RZBData::~RZBData() {
}

double RZBData::r() const {
    return _r;
}

double RZBData::z() const {
    return _z;
}

double RZBData::Br() const {
    return _Br;
}

double RZBData::Bz() const {
    return _Bz;
}
