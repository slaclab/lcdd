/*
 * CartesianXYZType.hh
 *
 *  Created on: Aug 11, 2014
 *      Author: jeremym
 */
#ifndef LCDD_SCHEMA_CARTESIANXYZTYPE_HH_
#define LCDD_SCHEMA_CARTESIANXYZTYPE_HH_ 1

#include "lcdd/schema/CartesianGridXYType.hh"

class CartesianGridXYZType : public CartesianGridXYType {

public:

    CartesianGridXYZType() {
    }

    virtual ~CartesianGridXYZType() {
    }

    void set_grid_size_z(const std::string grid_size_z) {
        _grid_size_z = grid_size_z;
    }

    const std::string& get_grid_size_z() {
        return _grid_size_z;
    }

    void set_offset_z(const std::string offset_z) {
        _offset_z = offset_z;
    }

    const std::string& get_offset_z() {
        return _offset_z;
    }

private:

    std::string _grid_size_z;
    std::string _offset_z;
};

#endif /* LCDD_SCHEMA_CARTESIANXYZTYPE_HH_ */
