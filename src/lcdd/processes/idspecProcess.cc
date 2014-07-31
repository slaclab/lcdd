// LCDD
#include "lcdd/schema/idspecElem.hh"

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
 * @brief SAX process for idspec element.
 */
class idspecProcess: public SAXStateProcess {
public:

    idspecProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~idspecProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "idspecProcess::StartElement() - " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        idspecElem* idspec = new idspecElem;

        idspec->set_name(attrs.getValue("name"));
        idspec->set_length(attrs.getValue("length"));

        m_obj = idspec;
        *obj = idspec;
    }
    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        SAXObject** so = Context()->GetTopObject();
        idspecElem* idspec = dynamic_cast<idspecElem*>(m_obj);
        idspec->add_content(name, *so);
    }

    virtual const std::string& State() const {
        static std::string tag = "idspec";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(idspecProcess)

