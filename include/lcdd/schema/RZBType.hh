// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/RZBType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $
#ifndef LCDD_SCHEMA_RZBTYPE_HH
#define LCDD_SCHEMA_RZBTYPE_HH 1

// STL
#include <string>

/**
 * @brief The RZBType from the schema.
 */
class RZBType {

public:

    /**
     * Class constructor.
     */
    RZBType() {
    }

    /**
     * Class destructor.
     */
    virtual ~RZBType() {
    }

    /**
     * Set the radius.
     * @param r The radius [radians].
     */
    void set_r(const std::string& r) {
        _r = r;
    }

    /**
     * Set the z position.
     * @param z The z position.
     */
    void set_z(const std::string& z) {
        _z = z;
    }

    /**
     * Set the Br value.
     * @param Br The Br value.
     */
    void set_Br(const std::string& Br) {
        _Br = Br;
    }

    /**
     * Set the Bz value.
     * @param Bz The Bz value.
     */
    void set_Bz(const std::string& Bz) {
        _Bz = Bz;
    }

    /**
     * Get the radius.
     * @return The radius.
     */
    const std::string& get_r() const {
        return _r;
    }

    /**
     * Get the z position.
     * @return The z position.
     */
    const std::string& get_z() const {
        return _z;
    }

    /**
     * Get the Br value.
     * @return The Br value.
     */
    const std::string& get_Br() const {
        return _Br;
    }

    /**
     * Get the Bz value.
     * @return The Bz value.
     */
    const std::string& get_Bz() const {
        return _Bz;
    }

public:
    std::string _r;
    std::string _z;
    std::string _Br;
    std::string _Bz;
};

#endif
