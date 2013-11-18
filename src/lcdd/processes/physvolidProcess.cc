// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/physvolidProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/physvolidElem.hh"

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
 * @brief SAX process for physvolid element.
 */
class physvolidProcess: public SAXStateProcess {
public:
    physvolidProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~physvolidProcess() {
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        physvolidElem* pvid = new physvolidElem;

        pvid->set_value(attrs.getValue("value"));
        pvid->set_field_name(attrs.getValue("field_name"));

        m_obj = pvid;
        *obj = pvid;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "physvolid";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(physvolidProcess)
