// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/tracker.hh"
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/detectors/TrackerSD.hh"
#include "lcdd/detectors/SensitiveDetectorFactory.hh"

// STL
#include <iostream>

/**
 * @brief Creates TrackerSD objects from tracker elements.
 */
class trackerSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    trackerSubscriber() {
        Subscribe("tracker");
    }

    virtual ~trackerSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        SensitiveDetectorFactory::createSensitiveDetector(object);
    }
};

DECLARE_SUBSCRIBER_FACTORY(trackerSubscriber)
