// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"
#include "G4Evaluator/GDMLExpressionEvaluator.h"

// LCDD
#include "lcdd/bfield/Dipole.hh"
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/dipole.hh"
#include "lcdd/schema/dipole_coeff.hh"

/**
 * @brief Creates G4Dipole runtime objects from dipole elements.
 */
class dipoleSubscriber: virtual public SAXSubscriber {

public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    dipoleSubscriber() {
        Subscribe("dipole");
    }

    virtual ~dipoleSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        if (object) {
            const dipole* d = dynamic_cast<const dipole*>(object);

            if (d) {
                double zmin, zmax, rmax;

                std::string lunit = d->get_lunit();
                std::string funit = d->get_funit();

                // Evaluate zmin with lunit.
                std::string sval = d->get_zmin();
                sval += "*" + lunit;
                zmin = calc->Eval(sval);

                // Evaluate zmax with lunit.
                sval = d->get_zmax();
                sval += "*" + lunit;
                zmax = calc->Eval(sval);

                // Evaluate rmax with lunit.
                sval = d->get_rmax();
                sval += "*" + lunit;
                rmax = calc->Eval(sval);

                // Create the Geant4 dipole object.
                Dipole* g4d = new Dipole();

                // Set the field unit's value.
                g4d->setFieldUnit(calc->Eval(funit));

                // Set the length unit's value.
                g4d->setLengthUnit(calc->Eval(lunit));

                // Set zmin and zmax.
                g4d->setZMax(zmax);
                g4d->setZMin(zmin);
                g4d->setRMax(rmax);

                // Add the dipole coefficients.
                ContentSequence* seq = const_cast<ContentSequence*>(d->get_content());
                size_t count = seq->size();
                for (size_t i = 0; i < count; i++) {
                    const ContentGroup::ContentItem& elem = seq->content(i);
                    if (elem.tag == "dipole_coeff") {
                        dipole_coeff* coeff = dynamic_cast<dipole_coeff*>(elem.object);
                        g4d->addCoeff(calc->Eval(coeff->get_value()));
                    } else {
                        std::cerr << "dipoleSubscriber :: Activate - The child element " << elem.tag << " is not a dipole_coeff!" << std::endl;
                    }
                }

                // Add the G4Dipole to the magnetic field store.
                std::string field_name = d->get_name();
                LCDDProcessor::instance()->addMagneticField(field_name, g4d);
            } else {
                std::cerr << "dipoleSubscriber :: Activate - Failed cast to dipole!" << std::endl;
            }
        }
    }
    ;
};

DECLARE_SUBSCRIBER_FACTORY(dipoleSubscriber)
