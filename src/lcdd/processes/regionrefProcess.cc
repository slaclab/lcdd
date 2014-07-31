// GDML
#include "Processes/ReferenceTypeProcess.h"

// LCDD
#include "lcdd/schema/RegionType.hh"

/**
 * @brief SAX process for regionref element.
 * @note  Extends ReferenceTypeProcess for reference to region element.
 */
class regionrefProcess: public ReferenceTypeProcess {
public:
    regionrefProcess(const ProcessingContext* context = 0) :
            ReferenceTypeProcess(context) {
    }

    virtual ~regionrefProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        RegionType::regionref* regref = new RegionType::regionref;

        *obj = regref;
        m_obj = regref;

        ReferenceTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string& name) {
        ReferenceTypeProcess::EndElement(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "regionref";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(regionrefProcess)
