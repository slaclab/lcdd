// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/SensitiveDetectorType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_SENSITIVEDETECTORTYPE_HH
#define LCDD_SCHEMA_SENSITIVEDETECTORTYPE_HH 1

// GDML
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"

// std
#include <string>

/**
 * @brief The SensitiveDetectorType from the schema.
 */
class SensitiveDetectorType {
public:

    /**
     * @class SensitiveDetectorType::sdref
     * @brief Reference to sd element.
     */
    class sdref: public SAXObject, public ReferenceType {
    public:

        /**
         * Class constructor.
         */
        sdref() {
        }

        /**
         * Class destructor.
         */
        virtual ~sdref() {
        }

        /**
         * Get the XML object type.
         * @return The XML object type (element).
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    SensitiveDetectorType() {
    }

    /**
     * Class destructor.
     */
    virtual ~SensitiveDetectorType() {
    }

    /**
     * Set the name of the sensitive detector.
     * @param n The name of the sensitive detector.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set the name of the detector's hits collection.
     * @param hcn The name of the hits collection.
     */
    void set_hitsCollectionName(const std::string& hcn) {
        _hitsCollectionName = hcn;
    }

    /**
     * Get the name of the hits collection.
     * @return The name of the hits collection.
     */
    const std::string& get_hitsCollectionName() const {
        return _hitsCollectionName;
    }

    /**
     * Set the step energy cut for hit processing.
     * @param ec The energy cut.
     */
    void set_ecut(const std::string& ec) {
        _ecut = ec;
    }

    /**
     * Set the unit for the energy cut.
     * @param eu The energy unit.
     */
    void set_eunit(const std::string& eu) {
        _eunit = eu;
    }

    /**
     * Set the verbosity value; 0 for least verbose; 2 for most.
     * @param v Set the verbosity value.
     */
    void set_verbose(const std::string& v) {
        _verbose = v;
    }

    /**
     * Get the type of the sensitive detector.
     * This should be "calorimeter" or "tracker".
     * @param t The sensitive detector type.
     */
    void set_type(const std::string& t) {
        _type = t;
    }

    /**
     * Set the endcap flag which should be "true" if detector
     * is an endcap and "false" if not.
     * @param e The endcap flag.
     */
    void set_endcap_flag(const std::string& e) {
        _endcapFlag = e;
    }

    /**
     * Get the name of the sensitive detector.
     * @return The name of the sensitive detector.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the energy cut unit.
     * @return The energy cut unit.
     */
    const std::string& get_eunit() const {
        return _eunit;
    }

    /**
     * Get the energy cut unit.
     * @return The energy cut unit.
     */
    const std::string& get_ecut() const {
        return _ecut;
    }

    /**
     * Get the verbosity level.
     * @return The verbosity level.
     */
    const std::string& get_verbose() const {
        return _verbose;
    }

    /**
     * Get the type of the sensitive detector.
     * @return The type of the sensitive detector.
     */
    const std::string& get_type() const {
        return _type;
    }

    /**
     * Get the endcap flag.
     * @return The endcap flag.
     */
    const std::string& get_endcap_flag() const {
        return _endcapFlag;
    }

    /**
     * Get the object's child content.
     * @return The object's child content.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

    /**
     * Add child content.
     * @param tag The child's tag.
     * @param so The child's SAXObject.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

private:

    ContentSequence _sequence;
    std::string _name;
    std::string _hitsCollectionName;
    std::string _endcapFlag;
    std::string _eunit;
    std::string _ecut;
    std::string _verbose;
    std::string _type;
};

#endif
