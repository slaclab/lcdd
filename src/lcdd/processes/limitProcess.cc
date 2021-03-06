// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/limit.hh"

/**
 * @brief SAX process for limit elements.
 */
class limitProcess: public SAXStateProcess {

public:
    limitProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~limitProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        limit* lim = new limit;

        lim->set_name(attrs.getValue("name"));
        lim->set_value(attrs.getValue("value"));
        lim->set_particles(attrs.getValue("particles"));
        lim->set_unit(attrs.getValue("unit"));

        m_obj = lim;
        *obj = lim;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "limit";
        return tag;
    }

private:

    SAXObject* m_obj;

};

DECLARE_PROCESS_FACTORY(limitProcess)
