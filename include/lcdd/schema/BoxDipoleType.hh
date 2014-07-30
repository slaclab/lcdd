#ifndef LCDD_SCHEMA_BOXDIPOLETYPE_HH_
#define LCDD_SCHEMA_BOXDIPOLETYPE_HH_ 1

// LCDD
#include "FieldType.hh"

/**
 * @brief The BoxDipoleType from the schema.
 */
class BoxDipoleType: public FieldType {

public:

    /**
     * Class constructor.
     */
    BoxDipoleType() {
    }

    /**
     * Class destructor.
     */
    virtual ~BoxDipoleType() {
    }

public:

    /**
     * Set the x position.
     * @param s The x position.
     */
    void set_x(const std::string& s) {
        _x = s;
    }

    /**
     * Set the y position.
     * @param s The y position.
     */
    void set_y(const std::string& s) {
        _y = s;
    }

    /**
     * Set the z position.
     * @param s The z position.
     */
    void set_z(const std::string& s) {
        _z = s;
    }

    /**
     * Set the x half dimension of the box.
     * @param s The box's x half dimension.
     */
    void set_dx(const std::string& s) {
        _dx = s;
    }

    /**
     * Set the y half dimension of the box.
     * @param s The box's y  half dimension.
     */
    void set_dy(const std::string& s) {
        _dy = s;
    }

    /**
     * Set the z half dimension of the box.
     * @param s The box's z half dimension.
     */
    void set_dz(const std::string& s) {
        _dz = s;
    }

    /**
     * Set the fixed Bx component for the region.
     * @param s The Bx component.
     */
    void set_bx(const std::string& s) {
        _bx = s;
    }

    /**
     * Set the fixed By component for the region.
     * @param s The By component.
     */
    void set_by(const std::string& s) {
        _by = s;
    }

    /**
     * Set the fixed Bz component for the region.
     * @param s The Bz component.
     */
    void set_bz(const std::string& s) {
        _bz = s;
    }

    /**
     * Get the x position.
     * @return The x position.
     */
    const std::string& get_x() const {
        return _x;
    }

    /**
     * Get the y position.
     * @return The y position.
     */
    const std::string& get_y() const {
        return _y;
    }

    /**
     * Get the z position.
     * @return The z position.
     */
    const std::string& get_z() const {
        return _z;
    }

    /**
     * Get the box half dimension in x.
     * @return The box half dimension in x.
     */
    const std::string& get_dx() const {
        return _dx;
    }

    /**
     * Get the box half dimension in y.
     * @return The box half dimension in y.
     */
    const std::string& get_dy() const {
        return _dy;
    }

    /**
     * Get the box half dimension in z.
     * @return The box half dimension in z.
     */
    const std::string& get_dz() const {
        return _dz;
    }

    /**
     * Get the fixed Bx component.
     * @return The Bx component.
     */
    const std::string& get_bx() const {
        return _bx;
    }

    /**
     * Get the fixed By component.
     * @return The By component.
     */
    const std::string& get_by() const {
        return _by;
    }

    /**
     * Get the fixed Bz component.
     * @return The Bz component.
     */
    const std::string& get_bz() const {
        return _bz;
    }

private:

    std::string _x;
    std::string _y;
    std::string _z;
    std::string _dx;
    std::string _dy;
    std::string _dz;
    std::string _bx;
    std::string _by;
    std::string _bz;
};

#endif
