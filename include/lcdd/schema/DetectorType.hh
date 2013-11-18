// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/DetectorType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_DETECTORTYPE_HH
#define LCDD_SCHEMA_DETECTORTYPE_HH 1

// STL
#include <string>

/**
 * @brief The DetectorType from the schema.
 */
class DetectorType {
public:

    /**
     * Class constructor.
     */
    DetectorType() {
    }

    /**
     * Class destructor.
     */
    virtual ~DetectorType() {
    }

public:

    /**
     * Set the name.
     * @param[i] The name.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set the version.
     * @param v The version.
     */
    void set_version(const std::string& v) {
        _version = v;
    }

    /**
     * Set the URL.
     * @param u The URL.
     */
    void set_url(const std::string& u) {
        _url = u;
    }

    /**
     * Get the name.
     * @return The name.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the version.
     * @return The version.
     */
    const std::string& get_version() const {
        return _version;
    }

    /**
     * Get the URL.
     * @return The URL.
     */
    const std::string& get_url() const {
        return _url;
    }

private:
    std::string _name;
    std::string _version;
    std::string _url;
};

#endif
