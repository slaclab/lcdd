// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/dipole_coeffProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/dipole_coeff.hh"

// STL
#include <iostream>

/**
 * @class dipole_coeffProcess
 * @brief SAX process to create the dipole_coeff element.
 */
class dipole_coeffProcess: public SAXStateProcess {
public:

    dipole_coeffProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~dipole_coeffProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        dipole_coeff* dpc = new dipole_coeff;

        dpc->set_value(attrs.getValue("value"));

        m_obj = dpc;
        *obj = dpc;
    }
    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "dipole_coeff";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(dipole_coeffProcess)
