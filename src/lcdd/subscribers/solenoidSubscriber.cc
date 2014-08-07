// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"
#include "G4Evaluator/GDMLExpressionEvaluator.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/solenoid.hh"
#include "lcdd/bfield/Solenoid.hh"

/**
 * @brief Creates Solenoid objects from solenoid elements.
 */
class solenoidSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    solenoidSubscriber() {
        Subscribe("solenoid");
    }

    virtual ~solenoidSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
        if (object != 0) {
            const solenoid* obj = dynamic_cast<const solenoid*>(object);

            if (obj) {

                double outer_field, inner_field;
                double zmin, zmax;
                double inner_radius, outer_radius;

                std::string lunit = obj->get_lunit();
                std::string funit = obj->get_funit();

                std::string sval = obj->get_innerField();
                sval += "*" + funit;
                inner_field = calc->Eval(sval);

                sval = obj->get_outerField();
                sval += "*" + funit;
                outer_field = calc->Eval(sval);

                sval = obj->get_zmin();
                sval += "*" + lunit;
                zmin = calc->Eval(sval);

                sval = obj->get_zmax();
                sval += "*" + lunit;
                zmax = calc->Eval(sval);

                sval = obj->get_innerRadius();
                sval += "*" + lunit;
                inner_radius = calc->Eval(sval);

                sval = obj->get_outerRadius();
                sval += "*" + lunit;
                outer_radius = calc->Eval(sval);

                Solenoid* sol = new Solenoid();

                sol->setInnerField(inner_field);
                sol->setOuterField(outer_field);
                sol->setInnerZ(zmin);
                sol->setOuterZ(zmax);
                sol->setInnerR(inner_radius);
                sol->setOuterR(outer_radius);

                std::string field_name = obj->get_name();
                LCDDProcessor::instance()->addMagneticField(field_name, sol);
            } else {
                std::cerr << "Failed cast to solenoid!" << std::endl;
            }
        }

        //delete object;
    }
};

DECLARE_SUBSCRIBER_FACTORY(solenoidSubscriber)

