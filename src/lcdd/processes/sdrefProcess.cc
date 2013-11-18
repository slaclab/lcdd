// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/sdrefProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/SensitiveDetectorType.hh"

// GDML
#include "Processes/ReferenceTypeProcess.h"

// STL
#include <iostream>

/**
 @class sdrefProcess
 @brief SAX process for sdref element.
 @note  Extends ReferenceTypeProcess for reference to sd element.
 */
class sdrefProcess: public ReferenceTypeProcess {
public:
    sdrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~sdrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        SensitiveDetectorType::sdref* s = new SensitiveDetectorType::sdref;

        *obj = s;
        m_obj = s;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "sdref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(sdrefProcess)
