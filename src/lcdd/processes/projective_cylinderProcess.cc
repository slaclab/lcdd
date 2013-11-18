// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/projective_cylinderProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/projective_cylinder.hh"

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
class projective_cylinderProcess: public SAXStateProcess {

public:

    projective_cylinderProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~projective_cylinderProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "projective_cylinderProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        projective_cylinder* prj = new projective_cylinder;

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
        static std::string tag = "projective_cylinder";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(projective_cylinderProcess)

