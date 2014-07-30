#ifndef LCDD_SCHEMA_FIELDMAP3DTYPE_HH_
#define LCDD_SCHEMA_FIELDMAP3DTYPE_HH_ 1

// LCDD
#include "FieldMapType.hh"

// STL
#include <string>

/**
 * @brief The FieldMapType from the schema.
 */
class FieldMap3DType: public FieldMapType {

public:

    /**
     * Class constructor.
     */
    FieldMap3DType() {
    }

    /**
     * Class destructor.
     */
    virtual ~FieldMap3DType() {
    }

    /**
     * Set the filename containing the field map data.
     * @param filename The path of the file containing the field map data.
     */
    void set_filename(const std::string& filename) {
        _filename = filename;
    }

    /**
     * Get the filename of the field map data.
     * @return The filename with the field map data.
     */
    const std::string& get_filename() const {
        return _filename;
    }

    /**
     * Set the x offset of the map.
     * @param xoffset The x offset.
     */
    void set_xoffset(const std::string& xoffset) {
        _xoffset = xoffset;
    }

    /**
     * Set the y offset of the map.
     * @param yoffset The y offset.
     */
    void set_yoffset(const std::string& yoffset) {
        _yoffset = yoffset;
    }

    /**
     * Set the z offset of the map.
     * @param zoffset The z offset.
     */
    void set_zoffset(const std::string& zoffset) {
        _zoffset = zoffset;
    }

    /**
     * Get the x offset of the map.
     * @return The x offset.
     */
    const std::string& get_xoffset() const {
        return _xoffset;
    }

    /**
     * Get the y offset of the map.
     * @return The y offset.
     */
    const std::string& get_yoffset() const {
        return _yoffset;
    }

    /**
     * Get the z offset of the map.
     * @return The z offset.
     */
    const std::string& get_zoffset() const {
        return _zoffset;
    }

private:

    std::string _filename;
    std::string _xoffset, _yoffset, _zoffset;
};

#endif
