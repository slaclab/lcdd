// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/GeneratorType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_GENERATORTYPE_HH
#define LCDD_SCHEMA_GENERATORTYPE_HH 1

// STL
#include <string>

/**
 * @brief The GeneratorType from the schema.
 */
class GeneratorType {
public:

    /**
     * Class constructor.
     */
    GeneratorType() {
    }

    /**
     * Class destructor.
     */
    virtual ~GeneratorType() {
    }

    /**
     * Set the name of the generator.
     * @param n The name of the generator.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set the version of the generator.
     * @param v The version of the generator.
     */
    void set_version(const std::string& v) {
        _version = v;
    }

    /**
     * Set the file from which the LCDD was generated.
     * @param u The file that generated the LCDD.
     */
    void set_file(const std::string& u) {
        _file = u;
    }

    /**
     * Set the checksum of the LCDD file.
     * @param c The checksum of the LCDD file.
     */
    void set_checksum(const std::string& c) {
        _checksum = c;
    }

    /**
     * Get the name of the generator.
     * @return The name of the generator.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the version of the generator.
     * @return The version of the generator.
     */
    const std::string& get_version() const {
        return _version;
    }

    /**
     * Get the file from which the LCDD was generated.
     * @return The file that generated the LCDD.
     */
    const std::string& get_file() const {
        return _file;
    }

    /**
     * Get the checksum of the LCDD file.
     * @return The checksum of the file.
     */
    const std::string& get_checksum() const {
        return _checksum;
    }

private:

    std::string _name;
    std::string _version;
    std::string _file;
    std::string _checksum;
};

#endif
