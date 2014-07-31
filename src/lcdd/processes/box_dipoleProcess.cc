// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/box_dipole.hh"
#include "lcdd/processes/FieldTypeProcess.hh"

// STL
#include <iostream>

/**
 * @brief SAX process for box_dipole element.
 */
class box_dipoleProcess: public FieldTypeProcess {
public:

    box_dipoleProcess(const ProcessingContext* context = 0) :
            FieldTypeProcess(context) {
    }

    virtual ~box_dipoleProcess() {
    }

    void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        box_dipole* x = new box_dipole;

        x->set_x(attrs.getValue("x"));
        x->set_y(attrs.getValue("y"));
        x->set_z(attrs.getValue("z"));
        x->set_dx(attrs.getValue("dx"));
        x->set_dy(attrs.getValue("dy"));
        x->set_dz(attrs.getValue("dz"));
        x->set_bx(attrs.getValue("bx"));
        x->set_by(attrs.getValue("by"));
        x->set_bz(attrs.getValue("bz"));

        _obj = x;
        *obj = x;

        FieldTypeProcess::StartElement(name, attrs);
    }

    void EndElement(const std::string&) {
    }

    void Characters(const std::string&) {
    }

    void StackPopNotify(const std::string&) {
    }

    const std::string& State() const {
        static std::string tag = "box_dipole";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(box_dipoleProcess)

