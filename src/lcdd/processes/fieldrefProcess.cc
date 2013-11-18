// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/fieldrefProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// GDML
#include "Processes/ReferenceTypeProcess.h"

// LCDD
#include "lcdd/schema/FieldType.hh"

/**
 * @brief SAX process for fieldref element.
 */
class fieldrefProcess: public ReferenceTypeProcess {
public:
    fieldrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~fieldrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        FieldType::fieldref* fref = new FieldType::fieldref;

        *obj = fref;
        m_obj = fref;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "fieldref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(fieldrefProcess)
