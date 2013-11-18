// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/colorProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/schema/color.hh"

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
 @class colorProcess
 @brief SAX process for color element.
 */
class colorProcess: public SAXStateProcess {
public:

    colorProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~colorProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "color::StartElement()" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        color* c = new color;

        c->set_R(attrs.getValue("R"));
        c->set_G(attrs.getValue("G"));
        c->set_B(attrs.getValue("B"));
        c->set_alpha(attrs.getValue("alpha"));

        m_obj = c;
        *obj = c;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "color";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(colorProcess)
