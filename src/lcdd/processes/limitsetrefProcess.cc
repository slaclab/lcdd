// GDML
#include "Processes/ReferenceTypeProcess.h"

// LCDD
#include "lcdd/schema/LimitSetType.hh"

/**
 * @brief SAX process for limitsetref element.
 */
class limitsetrefProcess: public ReferenceTypeProcess {
public:
    limitsetrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~limitsetrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        LimitSetType::limitsetref* lref = new LimitSetType::limitsetref;

        *obj = lref;
        m_obj = lref;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "limitsetref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(limitsetrefProcess)
