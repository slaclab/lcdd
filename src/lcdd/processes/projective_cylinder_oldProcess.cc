// LCDD
#include "lcdd/schema/projective_cylinder_old.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// STL
#include <iostream>

/**
 * @brief SAX process for projective_cylinder element.
 */
class projective_cylinder_oldProcess: public SAXStateProcess {

public:

    projective_cylinder_oldProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~projective_cylinder_oldProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "projective_cylinderProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        projective_cylinder_old* prj = new projective_cylinder_old;

        prj->set_ntheta(attrs.getValue("ntheta"));
        prj->set_nphi(attrs.getValue("nphi"));

        m_obj = prj;
        *obj = prj;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "projective_cylinder_old";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(projective_cylinder_oldProcess)
