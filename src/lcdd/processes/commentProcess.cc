// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/commentProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/comment.hh"

// STL
#include <iostream>

/**
 @class commentProcess
 @brief SAX process for comment element.
 */
class commentProcess: public SAXStateProcess {
public:
    commentProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }
    virtual ~commentProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList&) {
        //std::cout << "commentProcess::StartElement" << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        comment* c = new comment;

        m_obj = c;
        *obj = c;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string& cdata) {
        //std::cout << "commentProcess::Characters() - <" << cdata << ">" << std::endl;
        comment* c = dynamic_cast<comment*>(m_obj);
        c->set_comment(cdata);
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "comment";
        return tag;
    }

private:
    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(commentProcess)
