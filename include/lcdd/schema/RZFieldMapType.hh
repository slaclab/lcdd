// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/RZFieldMapType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_RZFIELDMAPTYPE_HH
#define LCDD_SCHEMA_RZFIELDMAPTYPE_HH 1

// LCDD
#include "FieldMapType.hh"

/**
 * @brief The RZFieldMapType from the schema.
 */
class RZFieldMapType: public FieldMapType {

public:

    /**
     * Class constructor.
     */
    RZFieldMapType() {
    }

    /**
     * Class destructor.
     */
    virtual ~RZFieldMapType() {
    }

    /**
     * Set the number of bins in r (radius).
     * @param num_bins_r The number of bins in r.
     */
    void set_num_bins_r(const std::string& num_bins_r) {
        _num_bins_r = num_bins_r;
    }

    /**
     * Get the number of bins in r.
     * @return The number of bins in r.
     */
    const std::string& get_num_bins_r() const {
        return _num_bins_r;
    }

    /**
     * Set the r grid size.
     * @param grid_size_r The r grid size.
     */
    void set_grid_size_r(const std::string& grid_size_r) {
        _grid_size_r = grid_size_r;
    }

    /**
     * Get the r grid size.
     * @return The r grid size.
     */
    const std::string& get_grid_size_r() const {
        return _grid_size_r;
    }

    /**
     * Set the number of z bins.
     * @param num_bins_z The number of z bins.
     */
    void set_num_bins_z(const std::string& num_bins_z) {
        _num_bins_z = num_bins_z;
    }

    /**
     * Get the number of z bins.
     * @return The number of z bins.
     */
    const std::string& get_num_bins_z() const {
        return _num_bins_z;
    }

    /**
     * Set the z grid size.
     * @param grid_size_z The z grid size.
     */
    void set_grid_size_z(const std::string& grid_size_z) {
        _grid_size_z = grid_size_z;
    }

    /**
     * Get the z grid size.
     * @return The z grid size.
     */
    const std::string& get_grid_size_z() const {
        return _grid_size_z;
    }

private:
    std::string _num_bins_r;
    std::string _grid_size_r;
    std::string _num_bins_z;
    std::string _grid_size_z;
};

#endif
