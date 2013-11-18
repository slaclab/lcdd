// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/VisType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_VISTYPE_HH
#define LCDD_SCHEMA_VISTYPE_HH 1

// GDML
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"

// std
#include <string>

/**
 * @brief The VisType from the schema.
 */
class VisType {
public:
    /**
     * @brief A reference to a vis element.
     */
    class visref: public SAXObject, public ReferenceType {
    public:

        /**
         * Class constructor.
         */
        visref() {
        }

        /**
         * Class destructor.
         */
        virtual ~visref() {
        }

        /**
         * Get the object type.
         * @return The object type (element).
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    VisType() {
    }

    /**
     * Class destructor.
     */
    virtual ~VisType() {
    }

public:

    /**
     * Set the name of the visualization attributes.
     * @param n The name of the visualization attributes.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set visibility; "true" for visible and "false" if invisible.
     * @param v The visibility setting.
     */
    void set_visible(const std::string& v) {
        _visible = v;
    }

    /**
     * Set show daughter volumes; "true" for yes and "false" for no.
     * @param d Set show daughters.
     */
    void set_show_daughters(const std::string& d) {
        _showDaughters = d;
    }

    /**
     * Set the line style; see schema for valid values.
     * @param l The line style.
     */
    void set_line_style(const std::string& l) {
        _lineStyle = l;
    }

    /**
     * Set the drawing style; see schema for valid values.
     * @param d The drawing style.
     */
    void set_drawing_style(const std::string& d) {
        _drawingStyle = d;
    }

    /**
     * Get the name of the visualization attributes.
     * @return The name of the visualization attributes.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get visilibity setting.
     * @return The visibility setting.
     */
    const std::string& get_visible() const {
        return _visible;
    }

    /**
     * Get show daughters setting.
     * @return Show daughters setting.
     */
    const std::string& get_show_daughters() const {
        return _showDaughters;
    }

    /**
     * Get the line style.
     * @return The line style.
     */
    const std::string& get_line_style() const {
        return _lineStyle;
    }

    /**
     * Get the drawing style.
     * @return The drawing style.
     */
    const std::string& get_drawing_style() const {
        return _drawingStyle;
    }

    /**
     * Get the child content.
     * @return The child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

    /**
     * Add child content.
     * @param tag The child tag.
     * @param so The child's SAXObject.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

private:

    ContentSequence _sequence;
    std::string _name;
    std::string _visible;
    std::string _showDaughters;
    std::string _lineStyle;
    std::string _drawingStyle;
};

#endif
