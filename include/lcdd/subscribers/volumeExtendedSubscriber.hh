#ifndef LCDD_SUBSCRIBERS_VOLUMEEXTENDEDSUBSCRIBER_HH_
#define LCDD_SUBSCRIBERS_VOLUMEEXTENDEDSUBSCRIBER_HH_ 1

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"
#include "Schema/volume.h"
#include "Schema/physvol.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/core/PhysicsLimitSet.hh"
#include "lcdd/schema/sensitive_detector.hh"
#include "lcdd/schema/RegionType.hh"
#include "lcdd/schema/physvolidElem.hh"
#include "lcdd/schema/VisType.hh"
#include "lcdd/schema/limit.hh"
#include "lcdd/schema/LimitSetType.hh"

// Geant4
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4VisAttributes.hh"

// STL
#include <iostream>

/**
 * @brief Handles LCDD tags on GDML volume elements.
 * @note This is the main extension point of GDML within LCDD package.
 */
class volumeExtendedSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const;

public:
    volumeExtendedSubscriber();

    virtual ~volumeExtendedSubscriber();

    virtual void Activate(const SAXObject* object);
};

#endif
