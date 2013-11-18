// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/headerProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/schema/header.hh"

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
 * @brief SAX process for header element.
 */
class headerProcess: public SAXStateProcess {
public:
    headerProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~headerProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList&) {
        //std::cout << "headerProcess::StartElement" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        header* h = new header;

        m_obj = h;
        *obj = h;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        //std::cout << "headerProcess::StackPopNotify" << std::endl;

        SAXObject** so = Context()->GetTopObject();
        header* h = dynamic_cast<header*>(m_obj);

        h->add_content(name, *so);

    }

    virtual const std::string& State() const {
        static std::string tag = "header";
        return tag;
    }

private:
    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(headerProcess)
