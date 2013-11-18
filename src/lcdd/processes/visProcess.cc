// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/visProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/vis.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// std
#include <iostream>

/**
 * @brief SAX process for vis element.
 */
class visProcess: public SAXStateProcess {
public:

    visProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~visProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "visProcess::StartElement()" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        vis* v = new vis;

        v->set_name(attrs.getValue("name"));
        v->set_visible(attrs.getValue("visible"));
        v->set_show_daughters(attrs.getValue("show_daughters"));
        v->set_line_style(attrs.getValue("line_style"));
        v->set_drawing_style(attrs.getValue("drawing_style"));

        m_obj = v;
        *obj = v;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        // add all content
        SAXObject** so = Context()->GetTopObject();
        vis* v = dynamic_cast<vis*>(m_obj);
        v->add_content(name, *so);
    }

    virtual const std::string& State() const {
        static std::string tag = "vis";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(visProcess)
