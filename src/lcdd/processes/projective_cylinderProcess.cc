/*
 * projective_cylinderProcess.cc
 *
 *  Created on: Aug 12, 2014
 *      Author: jeremym
 */

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

        SAXObject** obj = Context()->GetTopObject();

        projective_cylinder* element = new projective_cylinder;

        element->set_theta_bins(attrs.getValue("theta_bins"));
        element->set_phi_bins(attrs.getValue("phi_bins"));
        element->set_offset_theta(attrs.getValue("offset_theta"));
        element->set_offset_phi(attrs.getValue("offset_phi"));

        m_obj = element;
        *obj = element;
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


