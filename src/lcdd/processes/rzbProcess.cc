// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/rzb.hh"

// STL
#include <iostream>

/**
 * @brief Processor for rzB elements.
 */
class rzbProcess: public SAXStateProcess {

public:
    rzbProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~rzbProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "rzbProcess::StartElement" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        rzb* row = new rzb;

        row->set_r(attrs.getValue("r"));
        row->set_z(attrs.getValue("z"));
        row->set_Br(attrs.getValue("Br"));
        row->set_Bz(attrs.getValue("Bz"));

        m_obj = row;
        *obj = row;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "rzB";
        return tag;
    }

private:

    SAXObject* m_obj;

};

DECLARE_PROCESS_FACTORY(rzbProcess)
