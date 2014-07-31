// LCDD
#include "lcdd/schema/VisType.hh"

// GDML
#include "Processes/ReferenceTypeProcess.h"

/**
 * @brief SAX process for visref element.
 * @note  Extends ReferenceTypeProcess for referencing the vis elements.
 */
class visrefProcess: public ReferenceTypeProcess {
public:
    visrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~visrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        VisType::visref* visref = new VisType::visref;

        *obj = visref;
        m_obj = visref;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "visref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(visrefProcess)
