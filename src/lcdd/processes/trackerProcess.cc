// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/trackerProcess.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/tracker.hh"
#include "lcdd/processes/SensitiveDetectorTypeProcess.hh"

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
 @class trackerProcess
 @brief SAX process for tracker element.
 */
class trackerProcess: public SensitiveDetectorTypeProcess {

public:
    trackerProcess(const ProcessingContext* context = 0) :
            SensitiveDetectorTypeProcess(context) {
    }

    virtual ~trackerProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        tracker* trk = new tracker;
        trk->set_combine_hits(attrs.getValue("combine_hits"));

        _obj = trk;
        *obj = trk;

        SensitiveDetectorTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        SensitiveDetectorTypeProcess::StackPopNotify(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "tracker";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(trackerProcess)
