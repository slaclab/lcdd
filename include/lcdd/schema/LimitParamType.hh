// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/LimitParamType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_LIMITPARAMTYPE_HH
#define LCDD_SCHEMA_LIMITPARAMTYPE_HH 1

// STL
#include <string>
#include <vector>

/**
 * @brief The LimitParamType from the schema.
 */
class LimitParamType {
public:

    /**
     * Class constructor.
     */
    LimitParamType() {
    }

    /**
     * Class destructor.
     */
    virtual ~LimitParamType() {
    }

    /**
     * Set the applicable particles using a comma delimited list.
     * @param p A comma delimited list of particle names.
     */
    void set_particles(const std::string& p) {
        _particles = p;
    }

    /**
     * Get the list of applicable particles.
     * @return The list of applicable particles.
     */
    const std::string& get_particles() const {
        return _particles;
    }

    /**
     * Set the name of the limit parameter.
     * @param n The name of the limit parameter.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Get the name of the limit parameter.
     * @return The name of the limit parameter.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Set the value of the limit.
     * @param v The value of the limit.
     */
    void set_value(const std::string& v) {
        _value = v;
    }

    /**
     * Get the value of the limit.
     * @return The value of the limit.
     */
    const std::string& get_value() const {
        return _value;
    }

    /**
     * Set the unit of the parameter.
     * @param u The unit of the parameter.
     */
    void set_unit(const std::string& u) {
        _unit = u;
    }

    /**
     * Get the unit of the parameter.
     * @return The unit of the parameter.
     */
    const std::string& get_unit() const {
        return _unit;
    }

public:
    std::string _particles;
    std::string _value;
    std::string _name;
    std::string _unit;
};

#endif
