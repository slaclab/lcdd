// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/idspecrefProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// GDML
#include "Processes/ReferenceTypeProcess.h"

// LCDD
#include "lcdd/schema/IdSpecType.hh"

// STL
#include <iostream>

/**
 * @brief SAX process for idspecref element.
 * @note  Extends ReferenceTypeProcess for reference to idspec element.
 */
class idspecrefProcess: public ReferenceTypeProcess {
public:
    idspecrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~idspecrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();
        IdSpecType::idspecref* s = new IdSpecType::idspecref;

        *obj = s;
        m_obj = s;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "idspecref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(idspecrefProcess)
