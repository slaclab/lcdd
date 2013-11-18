// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/limitrefProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// GDML
#include "Processes/ReferenceTypeProcess.h"

// LCDD
#include "lcdd/schema/LimitType.hh"

/**
 * @brief SAX process for limitref element.
 */
class limitrefProcess: public ReferenceTypeProcess {
public:
    limitrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~limitrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        //std::cout << "limitrefProcess" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        LimitType::limitref* lref = new LimitType::limitref;

        *obj = lref;
        m_obj = lref;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "limitref";
        return tag;
    }
};

//DECLARE_PROCESS_FACTORY(limitrefProcess);
