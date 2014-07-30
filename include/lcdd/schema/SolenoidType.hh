#ifndef LCDD_SCHEMA_SOLENOIDTYPE_HH_
#define LCDD_SCHEMA_SOLENOIDTYPE_HH_ 1

// LCDD
#include "FieldType.hh"

/**
 * @brief The SolenoidType from the schema.
 */
class SolenoidType: public FieldType {

public:

    /**
     * Class constructor.
     */
    SolenoidType() {
    }

    /**
     * Class destructor.
     */
    virtual ~SolenoidType() {
    }

public:

    /**
     * Set the fixed inner Bz value.
     * @param s The inner Bz value.
     */
    void set_innerField(const std::string& s) {
        _innerField = s;
    }

    /**
     * Set the fixed outer Bz value.
     * @param s The outer Bz value.
     */
    void set_outerField(const std::string& s) {
        _outerField = s;
    }

    /**
     * Set the minimum Z value defining where the outer field value will apply.
     * @param s The minimum Z value.
     */
    void set_zmin(const std::string& s) {
        _zmin = s;
    }

    /**
     * Set the maximum Z value defining where the field ends.
     * @param s The maximum Z value.
     */
    void set_zmax(const std::string& s) {
        _zmax = s;
    }

    /**
     * Set the inner radius.
     * @param s The inner radius.
     */
    void set_innerRadius(const std::string& s) {
        _innerRadius = s;
    }

    /**
     * Set the outer radius.
     * @param s The outer radius.
     */
    void set_outerRadius(const std::string& s) {
        _outerRadius = s;
    }

    /**
     * Get the inner Bz value.
     * @return The inner Bz value.
     */
    const std::string& get_innerField() const {
        return _innerField;
    }

    /**
     * Get the outer Bz value.
     * @return The outer Bz value.
     */
    const std::string& get_outerField() const {
        return _outerField;
    }

    /**
     * Get the minimum Z value.
     * @return The minimum Z.
     */
    const std::string& get_zmin() const {
        return _zmin;
    }

    /**
     * Get the maximum Z value.
     * @return The maximum Z value.
     */
    const std::string& get_zmax() const {
        return _zmax;
    }

    /**
     * Get the inner radius.
     * @return The inner radius.
     */
    const std::string& get_innerRadius() const {
        return _innerRadius;
    }

    /**
     * Get the outer radius.
     * @return The outer radius.
     */
    const std::string& get_outerRadius() const {
        return _outerRadius;
    }

private:

    std::string _innerField;
    std::string _outerField;
    std::string _zmin;
    std::string _zmax;
    std::string _innerRadius;
    std::string _outerRadius;
};

#endif
