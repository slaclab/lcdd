// LCDD
#include "lcdd/schema/limitset.hh"
#include "lcdd/schema/limit.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// Geant4
#include "globals.hh"

/**
 * @brief SAX process for limitset elements.
 */
class limitsetProcess: public SAXStateProcess {
public:
    limitsetProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~limitsetProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        limitset* lim = new limitset;
        lim->set_name(attrs.getValue("name"));

        m_obj = lim;
        *obj = lim;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        if (name == "limit") {
            SAXObject** so = Context()->GetTopObject();
            limitset* lim = dynamic_cast<limitset*>(m_obj);

            if (lim != 0) {
                lim->add_content(name, *so);
            } else {
                G4Exception("limitsetProcess::StackPopNotify()", "", FatalException, "Failed cast to limitset.");
            }
        } else {
            std::cerr << "limitsetProcess::StackPopNotify() - Got limitset content that wasn't limit." << std::endl;
        }
    }

    virtual const std::string& State() const {
        static std::string tag = "limitset";
        return tag;
    }

private:

    SAXObject* m_obj;

};

DECLARE_PROCESS_FACTORY(limitsetProcess)
