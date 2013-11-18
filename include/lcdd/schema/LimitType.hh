// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/LimitType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_LIMITTYPE_HH
#define LCDD_SCHEMA_LIMITTYPE_HH

// GDML
#include "Schema/ReferenceType.h"

// std
#include <string>

/**
 * @brief The LimitType from the schema.
 */
class LimitType {
public:

    /**
     * @brief A reference to a limit element.
     */
    class limitref: public SAXObject, public ReferenceType {
    public:

        /**
         * Class constructor.
         */
        limitref() {
        }

        /**
         * Class destructor.
         */
        virtual ~limitref() {
        }

        /**
         * Get the type of this SAXObject.
         * @return The type of this SAXObject.
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    LimitType() {
    }

    /**
     * Class destructor.
     */
    virtual ~LimitType() {
    }

    /**
     * Get the name of the physics limit.
     * @return The name of the physics limit.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the maximum step length.
     * @return The maximum step length.
     */
    const std::string& get_step_length_max() const {
        return _stepLengthMax;
    }

    /**
     * Get the maximum track length.
     * @return The maximum track length.
     */
    const std::string& get_track_length_max() const {
        return _trackLengthMax;
    }

    /**
     * Get the maximum time.
     * @return The maximum time.
     */
    const std::string& get_time_max() const {
        return _timeMax;
    }

    /**
     * Get the minimum kinetic energy.
     * @return The minimum kinetic energy.
     */
    const std::string& get_ekin_min() const {
        return _ekinMin;
    }

    /**
     * Get the minimum range.
     * @return The minimum range.
     */
    const std::string& get_range_min() const {
        return _rangeMin;
    }

    /**
     * Get the energy unit.
     * @return The energy unit.
     */
    const std::string& get_eunit() const {
        return _eunit;
    }

    /**
     * Get the length unit.
     * @return The length unit.
     */
    const std::string& get_lunit() const {
        return _lunit;
    }

    /**
     * Get the time unit.
     * @return The time unit.
     */
    const std::string& get_tunit() const {
        return _tunit;
    }

    /**
     * Set the name.
     * @param s The name.
     */
    void set_name(const std::string& s) {
        _name = s;
    }

    /**
     * Set the the maximum step length.
     * @param s The maximum step length.
     */
    void set_step_length_max(const std::string& s) {
        _stepLengthMax = s;
    }

    /**
     * Set the maximum track length.
     * @param s The maximum track length.
     */
    void set_track_length_max(const std::string& s) {
        _trackLengthMax = s;
    }

    /**
     * Set the maximum time.
     * @param s The maximum time.
     */
    void set_time_max(const std::string& s) {
        _timeMax = s;
    }

    /**
     * Set the minimum kinetic energy.
     * @param s The minimum kinetic energy.
     */
    void set_ekin_min(const std::string& s) {
        _ekinMin = s;
    }

    /**
     * Set the minimum range.
     * @param s The minimum range.
     */
    void set_range_min(const std::string& s) {
        _rangeMin = s;
    }

    /**
     * Set the energy unit.
     * @param s The energy unit.
     */
    void set_eunit(const std::string& s) {
        _eunit = s;
    }

    /**
     * Set the length unit.
     * @param s The length unit.
     */
    void set_lunit(const std::string& s) {
        _lunit = s;
    }

    /**
     * Set the time unit
     */
    void set_tunit(const std::string& s) {
        _tunit = s;
    }

private:

    std::string _name;

    std::string _stepLengthMax;
    std::string _trackLengthMax;
    std::string _timeMax;
    std::string _ekinMin;
    std::string _rangeMin;

    std::string _eunit;
    std::string _lunit;
    std::string _tunit;
};

#endif
