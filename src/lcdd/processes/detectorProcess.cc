// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/detectorProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/schema/detector.hh"

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
 * @brief SAX process for detector element.
 */
class detectorProcess: public SAXStateProcess {
public:
    detectorProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~detectorProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        detector* d = new detector;

        d->set_name(attrs.getValue("name"));
        d->set_version(attrs.getValue("version"));
        d->set_url(attrs.getValue("url"));

        m_obj = d;
        *obj = d;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "detector";
        return tag;
    }

private:
    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(detectorProcess)
