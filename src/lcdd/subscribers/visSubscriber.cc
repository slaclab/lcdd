// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/subscribers/visSubscriber.cc,v 1.3 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/vis.hh"
#include "lcdd/schema/color.hh"
#include "lcdd/util/StringUtil.hh"

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

// Geant4
#include "G4VisAttributes.hh"

/**
 * @brief Creates G4VisAttributes objects from vis elements.
 */
class visSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    visSubscriber() {
        Subscribe("vis");
    }

    virtual ~visSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        //std::cout << "visSubscriber::Activate()" << std::endl;

        if (object != 0) {
            const vis* vobj = dynamic_cast<const vis*>(object);

            if (vobj) {
                G4VisAttributes* g4vis = new G4VisAttributes;

                std::string name = vobj->get_name();
                bool visible = StringUtil::toBool(vobj->get_visible());
                bool show_daughters = StringUtil::toBool(vobj->get_show_daughters());
                G4VisAttributes::LineStyle line = convertLineStyle(vobj->get_line_style());
                G4VisAttributes::ForcedDrawingStyle draw = convertDrawingStyle(vobj->get_drawing_style());

                g4vis->SetVisibility(visible);
                g4vis->SetDaughtersInvisible(!show_daughters);
                g4vis->SetLineStyle(line);

                if (draw == G4VisAttributes::wireframe) {
                    g4vis->SetForceWireframe(true);
                } else if (draw == G4VisAttributes::solid) {
                    g4vis->SetForceSolid(true);
                }

                // set color
                bool color_set = false;
                ContentSequence* seq = const_cast<ContentSequence*>(vobj->get_content());
                size_t count = seq->size();
                for (size_t i = 0; i < count; i++) {
                    std::string child_tag = seq->content(i).tag;
                    SAXObject* child_obj = seq->content(i).object;

                    if (child_tag == "color") {
                        //std::cout << "handling color" << std::endl;
                        color* c = dynamic_cast<color*>(child_obj);

                        double r = StringUtil::toDouble(c->get_R());
                        double g = StringUtil::toDouble(c->get_G());
                        double b = StringUtil::toDouble(c->get_B());
                        double alpha = StringUtil::toDouble(c->get_alpha());

                        //std::cout << "r g b alpha: " << r << " " << g << " " << b << " " << alpha << std::endl;

                        g4vis->SetColor(r, g, b, alpha);

                        // should be only one	    
                        color_set = true;
                        break;
                    }
                }

                if (!color_set) {
                    std::cerr << "WARNING: Color was not explicitly set and got the default value." << std::endl;
                }

                // add to proc's map
                LCDDProcessor::instance()->addVisAttributes(name, g4vis);
            }
        }

        //delete object;
    }

    static G4VisAttributes::LineStyle convertLineStyle(const std::string& s) {
        G4VisAttributes::LineStyle l = G4VisAttributes::unbroken;

        if (s == "unbroken") {
            l = G4VisAttributes::unbroken;
        } else if (s == "dashed") {
            l = G4VisAttributes::dashed;
        } else if (s == "dotted") {
            l = G4VisAttributes::dotted;
        } else {
            std::cerr << "WARNING: unknown LineStyle - " << s << std::endl;
        }

        return l;
    }

    static G4VisAttributes::ForcedDrawingStyle convertDrawingStyle(const std::string& s) {
        G4VisAttributes::ForcedDrawingStyle d = G4VisAttributes::wireframe;
        if (s == "wireframe") {
            d = G4VisAttributes::wireframe;
        } else if (s == "solid") {
            d = G4VisAttributes::solid;
        } else {
            std::cerr << "WARNING: unknown DrawingStyle - " << d << std::endl;
        }

        return d;
    }
};

DECLARE_SUBSCRIBER_FACTORY(visSubscriber)
