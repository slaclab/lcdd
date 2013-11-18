// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/RegionType.hh,v 1.7 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_SCHEMA_REGIONTYPE_HH
#define LCDD_SCHEMA_REGIONTYPE_HH 1

// GDML
#include "Saxana/SAXObject.h"
#include "Schema/ReferenceType.h"
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"

/**
 * @brief The RegionType from the schema.
 */
class RegionType {

public:

    /**
     * @brief A reference to a region element.
     */
    class regionref: public SAXObject, public ReferenceType {

    public:

        /**
         * Class constructor.
         */
        regionref() {
        }

        /**
         * Class destructor.
         */
        virtual ~regionref() {
        }

        /**
         * Get the object XML type.
         * @return The object XML type.
         */
        virtual SAXObject::Type type() {
            return SAXObject::element;
        }
    };

public:

    /**
     * Class constructor.
     */
    RegionType() {
    }

    /**
     * Class destructor.
     */
    virtual ~RegionType() {
    }

    /**
     * Set the name of the region.
     * @param s The name of the region.
     */
    void set_name(const std::string& s) {
        _name = s;
    }

    /**
     * Set whether to store secondary particle information
     * as G4 trajectories in this region.
     * @param s Set whether to store secondary particle information.
     */
    void set_storeSecondaries(const std::string& s) {
        _storeSecondaries = s;
    }

    /**
     * Set whether to kill tracks that enter this region,
     * after their first step.
     * @param killTracks Set whether to kill tracks that enter this region.
     */
    void set_killTracks(const std::string& killTracks) {
        _killTracks = killTracks;
    }

    /**
     * Set the secondary production cut for this region.
     * This is the Geant4 "production cut" which is measured in length.
     * (See Geant4 documentation for details.)
     * @param s The secondary production cut.
     */
    void set_cut(const std::string& s) {
        _cut = s;
    }

    /**
     * Set the length unit for the production cut.
     * @param s The length unit for the production cut.
     */
    void set_lunit(const std::string& s) {
        _lunit = s;
    }

    /**
     * Set the trajectory energy threshold for the region.
     * @param s The trajectory energy threshold.
     */
    void set_threshold(const std::string& s) {
        _threshold = s;
    }

    /**
     * Set the energy unit for the energy threshold.
     */
    void set_eunit(const std::string& s) {
        _eunit = s;
    }

    /**
     * Get the name of the region.
     * @return The name of the region.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get whether to store track secondaries information to trajectories
     * or not in this region.
     * @return This is "true" to store secondaries and "false" if not.
     */
    const std::string& get_storeSecondaries() const {
        return _storeSecondaries;
    }

    /**
     * Get whether to kill tracks that enter this region, after their first step
     * in the region's volume.
     * @return This is "true" to kill tracks and "false" if not.
     */
    const std::string& get_killTracks() const {
        return _killTracks;
    }

    /**
     * Get the production cut for this region.
     * @return The production cut for the region.
     */
    const std::string& get_cut() const {
        return _cut;
    }

    /**
     * Get the length unit for the production cut.
     * @return The length unit for the production cut.
     */
    const std::string& get_lunit() const {
        return _lunit;
    }

    /**
     * Get the trajectory energy threshold.
     * @return The trajectory energy threshold.
     */
    const std::string& get_threshold() const {
        return _threshold;
    }

    /**
     * Get the energy unit for the trajectory threshold cut.
     * @return The energy unit for the threshold.
     */
    const std::string& get_eunit() const {
        return _eunit;
    }

    /**
     * Add XML contents.
     * @param tag The tag of the child.
     * @param so The SAXObject of the child.
     */
    void add_content(const std::string& tag, SAXObject* so) {
        ContentGroup::ContentItem ci = { tag, so };
        _sequence.add_content(ci);
    }

    /**
     * Get the XML contents.
     * @return The object's XML contents.
     */
    const ContentSequence* get_content() const {
        return &_sequence;
    }

private:

    ContentSequence _sequence;
    std::string _name;
    std::string _storeSecondaries;
    std::string _killTracks;
    std::string _cut;
    std::string _lunit;
    std::string _threshold;
    std::string _eunit;
};

#endif
