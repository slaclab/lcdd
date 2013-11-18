// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/dipoleProcess.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/schema/dipole.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

/**
 * @brief SAX process for the dipole element.
 */
class dipoleProcess: public SAXStateProcess {
public:

    dipoleProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~dipoleProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        dipole* d = new dipole;
        d->set_name(attrs.getValue("name"));
        d->set_lunit(attrs.getValue("lunit"));
        d->set_funit(attrs.getValue("funit"));
        d->set_zmax(attrs.getValue("zmax"));
        d->set_zmin(attrs.getValue("zmin"));
        d->set_rmax(attrs.getValue("rmax"));

        m_obj = d;
        *obj = d;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        SAXObject** so = Context()->GetTopObject();
        dipole* d = dynamic_cast<dipole*>(m_obj);
        d->add_content(name, *so);
    }

    virtual const std::string& State() const {
        static std::string tag = "dipole";
        return tag;
    }

private:
    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(dipoleProcess)
