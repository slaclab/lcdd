// LCDD
#include "lcdd/schema/author.hh"

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
 * @brief SAX process for author element.
 */
class authorProcess: public SAXStateProcess {

public:

    authorProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~authorProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "authorProcess::StartElement" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        author* a = new author;

        a->set_name(attrs.getValue("name"));
        a->set_email(attrs.getValue("email"));

        m_obj = a;
        *obj = a;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "author";
        return tag;
    }

private:
    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(authorProcess)
