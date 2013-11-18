// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/nonprojective_cylinderProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/nonprojective_cylinder.hh"

// STL
#include <iostream>

/**
 @class nonprojective_cylinderProcess
 @brief SAX process for nonprojective_cylinder element.
 */
class nonprojective_cylinderProcess: public SAXStateProcess {

public:

    nonprojective_cylinderProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~nonprojective_cylinderProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "nonprojective_cylinderProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        nonprojective_cylinder* np = new nonprojective_cylinder;

        np->set_gridSizeZ(attrs.getValue("grid_size_z"));
        np->set_gridSizePhi(attrs.getValue("grid_size_phi"));
        np->set_lunit(attrs.getValue("lunit"));

        m_obj = np;
        *obj = np;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "nonprojective_cylinder";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(nonprojective_cylinderProcess)
