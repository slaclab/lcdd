/*
 * CartesianGridXYType.hh
 *
 *  Created on: Aug 7, 2014
 *      Author: jeremym
 */
#ifndef LCDD_SCHEMA_CARTESIANGRIDXYTYPE_HH_
#define LCDD_SCHEMA_CARTESIANGRIDXYTYPE_HH_ 1

// LCDD
#include "SegmentationType.hh"

class CartesianGridXYType: public SegmentationType {

public:

    CartesianGridXYType() {
    }

    virtual ~CartesianGridXYType() {
    }

    void set_grid_size_x(const std::string grid_size_x) {
        _grid_size_x = grid_size_x;
    }

    const std::string& get_grid_size_x() {
        return _grid_size_x;
    }

    void set_grid_size_y(const std::string grid_size_y) {
        _grid_size_y = grid_size_y;
    }

    const std::string& get_grid_size_y() {
        return _grid_size_y;
    }

    void set_offset_x(const std::string offset_x) {
        _offset_x = offset_x;
    }

    const std::string& get_offset_x() {
        return _offset_x;
    }

    void set_offset_y(const std::string offset_y) {
        _offset_y = offset_y;
    }

    const std::string& get_offset_y() {
        return _offset_y;
    }

private:

    std::string _grid_size_x;
    std::string _grid_size_y;
    std::string _offset_x;
    std::string _offset_y;
};

#endif /* CARTESIANGRIDXYTYPE_HH_ */
