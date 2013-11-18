// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/subscribers/calorimeterSubscriber.cc,v 1.5 2013-11-13 23:02:59 jeremy Exp $

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/schema/calorimeter.hh"
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/detectors/CalorimeterSD.hh"
#include "lcdd/detectors/SensitiveDetectorFactory.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/id/IdSpec.hh"

// STL
#include <iostream>
#include <sstream>

/**
 * @brief SAX subscriber for calorimeter element.
 * @note  Delegates to SensitiveDetectorFactory to create G4CalorimeterSD object.
 */
class calorimeterSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    calorimeterSubscriber() {
        Subscribe("calorimeter");
    }

    virtual ~calorimeterSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        // use factory to create this SD
        SensitiveDetectorFactory::createSensitiveDetector(object);
    }
};

DECLARE_SUBSCRIBER_FACTORY(calorimeterSubscriber)
