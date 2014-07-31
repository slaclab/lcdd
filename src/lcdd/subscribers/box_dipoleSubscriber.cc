// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/bfield/BoxDipole.hh"
#include "lcdd/schema/box_dipole.hh"

// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"
#include "G4Evaluator/GDMLExpressionEvaluator.h"

/**
 * @brief Instantiate BoxDipole objects from box_dipole SAX elements.
 */
class box_dipoleSubscriber: virtual public SAXSubscriber {

public:

    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:

    box_dipoleSubscriber() {
        Subscribe("box_dipole");
    }

    virtual ~box_dipoleSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        if (object != 0) {
            const box_dipole* dipoleElement = dynamic_cast<const box_dipole*>(object);

            double x, y, z, dx, dy, dz, bx, by, bz;
            x = y = z = dx = dy = dz = bx = by = bz = 0;

            std::string lunit = dipoleElement->get_lunit();
            std::string funit = dipoleElement->get_funit();

            std::string val = dipoleElement->get_x();
            val += "*" + lunit;
            x = calc->Eval(val);

            val = dipoleElement->get_y();
            val += "*" + lunit;
            y = calc->Eval(val);

            val = dipoleElement->get_z();
            val += "*" + lunit;
            z = calc->Eval(val);

            val = dipoleElement->get_dx();
            val += "*" + lunit;
            dx = calc->Eval(val);

            val = dipoleElement->get_dy();
            val += "*" + lunit;
            dy = calc->Eval(val);

            val = dipoleElement->get_dz();
            val += "*" + lunit;
            dz = calc->Eval(val);

            val = dipoleElement->get_bx();
            val += "*" + funit;
            bx = calc->Eval(val);

            val = dipoleElement->get_by();
            val += "*" + funit;
            by = calc->Eval(val);

            val = dipoleElement->get_bz();
            val += "*" + funit;
            bz = calc->Eval(val);

            BoxDipole* boxDipole = new BoxDipole(x, y, z, dx, dy, dz, bx, by, bz);

            std::string fieldName = dipoleElement->get_name();
            LCDDProcessor::instance()->addMagneticField(fieldName, boxDipole);
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(box_dipoleSubscriber)
