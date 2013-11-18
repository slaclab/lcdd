// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/DipoleCoeffType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_DIPOLECOEFFTYPE_HH
#define LCDD_SCHEMA_DIPOLECOEFFTYPE_HH

// STL
#include <string>

/**
 * @brief The DipoleCoeffType from the schema.
 */
class DipoleCoeffType {
public:

    /**
     * Class constructor.
     */
    DipoleCoeffType() {
    }

    /**
     * Class destructor.
     */
    virtual ~DipoleCoeffType() {
    }

public:

    /**
     * Set the dipole coefficient value.
     * @param s The dipole coefficient value.
     */
    void set_value(const std::string& s) {
        _value = s;
    }

    /**
     * Get the dipole coefficient value.
     * @return The dipole coefficient value.
     */
    const std::string& get_value() {
        return _value;
    }

private:
    std::string _value;
};

#endif
