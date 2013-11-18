// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/schema/tracker.hh,v 1.6 2013-11-14 00:47:22 jeremy Exp $

#ifndef LCDD_SCHEMA_TRACKER_HH
#define LCDD_SCHEMA_TRACKER_HH 1

// LCDD
#include "TrackerType.hh"

// GDML
#include "Saxana/SAXObject.h"
#include "SensitiveDetectorType.hh"

/**
 * @brief The tracker element from the schema.
 */
class tracker: public SAXObject, public TrackerType {
public:

    /**
     * Class constructor.
     */
    tracker() {
    }

    /**
     * Class destructor.
     */
    virtual ~tracker() {
    }

    /**
     * Get the type of this SAXObject.
     * @return The type of this SAXObject.
     */
    virtual SAXObject::Type type() {
        //std::cout << "tracker::type()" << std::endl;
        return SAXObject::element;
    }
};

#endif
