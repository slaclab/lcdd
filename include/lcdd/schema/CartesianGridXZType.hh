/*
 * CartesianGridXYType.hh
 *
 *  Created on: Aug 7, 2014
 *      Author: jeremym
 */
#ifndef LCDD_SCHEMA_CARTESIANGRIDXZTYPE_HH_
#define LCDD_SCHEMA_CARTESIANGRIDXZTYPE_HH_ 1

// LCDD
#include "SegmentationType.hh"

class CartesianGridXZType: public SegmentationType {

public:

    CartesianGridXZType() {
    }

    virtual ~CartesianGridXZType() {
    }

    void set_grid_size_x(const std::string grid_size_x) {
        _grid_size_x = grid_size_x;
    }

    const std::string& get_grid_size_x() {
        return _grid_size_x;
    }

    void set_grid_size_z(const std::string grid_size_z) {
        _grid_size_z = grid_size_z;
    }

    const std::string& get_grid_size_z() {
        return _grid_size_z;
    }

    void set_offset_x(const std::string offset_x) {
        _offset_x = offset_x;
    }

    const std::string& get_offset_x() {
        return _offset_x;
    }

    void set_offset_z(const std::string offset_z) {
        _offset_z = offset_z;
    }

    const std::string& get_offset_z() {
        return _offset_z;
    }

private:

    std::string _grid_size_x;
    std::string _grid_size_z;
    std::string _offset_x;
    std::string _offset_z;
};

#endif /* LCDD_SCHEMA_CARTESIANGRIDXZTYPE_HH_ */
