// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/ColorType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_COLORTYPE_HH
#define LCDD_SCHEMA_COLORTYPE_HH 1

// STL
#include <string>

/**
 * @brief The ColorType from the schema.
 */
class ColorType {

public:

    /**
     * Class constructor.
     */
    ColorType() {
    }

    /**
     * Class destructor.
     */
    virtual ~ColorType() {
    }

    /**
     * Set the red color value.
     * @param[i] r The red color value.
     */
    void set_R(const std::string& r) {
        _R = r;
    }

    /**
     * Set the green color value.
     * @param[i] g The green color value.
     */
    void set_G(const std::string& g) {
        _G = g;
    }

    /**
     * Set the blue color value.
     * @param[i] b The blue color value.
     */
    void set_B(const std::string& b) {
        _B = b;
    }

    /**
     * Set the alpha value.
     * @param[i] a The alpha value.
     */
    void set_alpha(const std::string& a) {
        _alpha = a;
    }

    /**
     * Get the red value.
     * @return The red value.
     */
    const std::string& get_R() {
        return _R;
    }

    /**
     * Get the green value.
     * @return The green value.
     */
    const std::string& get_G() {
        return _G;
    }

    /**
     * Get the blue value.
     * @return The blue value.
     */
    const std::string& get_B() {
        return _B;
    }

    /**
     * Get the alpha value.
     * @return The alpha value.
     */
    const std::string& get_alpha() {
        return _alpha;
    }

private:
    std::string _R;
    std::string _G;
    std::string _B;
    std::string _alpha;
};

#endif
