#include "lcdd/schema/idfieldElem.hh"

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
 @class idfieldProcess
 @brief SAX process to create the idfield element.
 */
class idfieldProcess: public SAXStateProcess {
public:

    idfieldProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~idfieldProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        idfieldElem* idfield = new idfieldElem;

        idfield->set_label(attrs.getValue("label"));
        idfield->set_start(attrs.getValue("start"));
        idfield->set_length(attrs.getValue("length"));
        idfield->set_signed(attrs.getValue("signed"));

        m_obj = idfield;
        *obj = idfield;
    }
    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "idfield";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(idfieldProcess)
