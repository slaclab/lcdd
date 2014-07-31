// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/global_field.hh"
#include "lcdd/processes/SensitiveDetectorTypeProcess.hh"

// STL
#include <iostream>

/**
 * @brief SAX process for global_field element.
 */
class global_fieldProcess: public SAXStateProcess {
public:
    global_fieldProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~global_fieldProcess() {
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList&) {
        //std::cout << "global_fieldProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        global_field* cal = new global_field;

        m_obj = cal;
        *obj = cal;
    }

    virtual void EndElement(const std::string&) {
        //std::cout << "global_fieldProcess::EndElement: " << name << " " << std::endl;
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        //std::cout << "global_fieldProcess::StackPopNotify: " << name << std::endl;

        SAXObject** so = Context()->GetTopObject();
        global_field* fobj = dynamic_cast<global_field*>(m_obj);

        fobj->add_content(name, *so);
    }

    virtual const std::string& State() const {
        static std::string tag = "global_field";
        return tag;
    }

protected:
    SAXObject* m_obj;

};

DECLARE_PROCESS_FACTORY(global_fieldProcess)
