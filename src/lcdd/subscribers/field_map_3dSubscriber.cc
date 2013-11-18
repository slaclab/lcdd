// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/subscribers/field_map_3dSubscriber.cc,v 1.5 2013-11-13 23:02:59 jeremy Exp $

// lcdd
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/field_map_3d.hh"
#include "lcdd/bfield/Cartesian3DMagneticFieldMap.hh"

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentObject.h"
#include "Saxana/SAXComponentFactory.h"

// Geant4
#include "G4Processor/GDMLProcessor.h"

// STL
#include <iostream>

/**
 * @brief Creates FieldMap3D objects from field_map_3d elements.
 */
class field_map_3dSubscriber: virtual public SAXSubscriber {

public:

    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:

    field_map_3dSubscriber() {
        Subscribe("field_map_3d");
    }

    virtual ~field_map_3dSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {

        //std::cout << "field_map_3d::Subscriber" << std::endl;

        const field_map_3d* obj = dynamic_cast<const field_map_3d*>(object);

        if (object != 0) {

            if (obj) {

                if (obj) {

                    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
                    //std::string lunit = obj->get_lunit();
                    //std::string funit = obj->get_funit();

                    std::string name = obj->get_name();
                    std::string fileName = obj->get_filename();

                    // Check if file exists before creating field map.
                    std::ifstream ifile(fileName.c_str());
                    if (!ifile) {
                        std::cerr << "field map file does not exist at location: " << fileName << std::endl;
                        G4Exception("", "", FatalException, "Field map file does not exist.");
                    }

                    // Calculate offsets.
                    // TODO: Multiply by units.
                    double xoffset = calc->Eval(obj->get_xoffset());
                    double yoffset = calc->Eval(obj->get_yoffset());
                    double zoffset = calc->Eval(obj->get_zoffset());

                    Cartesian3DMagneticFieldMap* fmap = new Cartesian3DMagneticFieldMap(fileName.c_str(), xoffset, yoffset, zoffset);
                    LCDDProcessor::instance()->addMagneticField(name, fmap);
                }
            }
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(field_map_3dSubscriber)
