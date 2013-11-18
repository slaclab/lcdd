// $Id: global_fieldSubscriber.cc,v 1.3 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/global_field.hh"
#include "lcdd/schema/FieldType.hh"

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// Geant4
#include "G4MagneticField.hh"

// STL
#include <iostream>

/**
 * @brief Creates fields from global_field element.
 * @note  Resolves fieldref and sets global field in LCDDProcessor.
 */
class global_fieldSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    global_fieldSubscriber() {
        Subscribe("global_field");
    }

    virtual ~global_fieldSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        const global_field* fobj = 0;
        G4MagneticField* mag = 0;
        LCDDProcessor* proc = LCDDProcessor::instance();

        if (object != 0) {
            fobj = dynamic_cast<const global_field*>(object);

            if (fobj) {
                const ContentSequence* seq = fobj->get_content();

                size_t count = seq->size();

                for (size_t i = 0; i < count; i++) {
                    if (seq->content(i).tag == "fieldref") {
                        FieldType::fieldref* fref = dynamic_cast<FieldType::fieldref*>(seq->content(i).object);

                        mag = proc->getMagneticField(fref->get_ref());

                        if (mag != 0) {
                            LCDDProcessor::instance()->addGlobalField(mag);
                        }
                    }
                }

            } else {
                std::cerr << "Failed cast to global_field!" << std::endl;
            }
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(global_fieldSubscriber)

