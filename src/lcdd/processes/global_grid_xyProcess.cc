// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/global_grid_xyProcess.cc,v 1.4 2013-11-13 23:02:57 jeremy Exp $

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/global_grid_xy.hh"

// STL
#include <iostream>

/**
 * @brief SAX process for global_grid_xyz elements.
 */
class global_grid_xyProcess: public SAXStateProcess {

public:

    global_grid_xyProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~global_grid_xyProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        global_grid_xy* np = new global_grid_xy;

        np->set_lunit(attrs.getValue("lunit"));

        np->set_grid_size_x(attrs.getValue("grid_size_x"));
        np->set_grid_size_y(attrs.getValue("grid_size_y"));

        m_obj = np;
        *obj = np;
    }

    virtual void EndElement(const std::string&) {
        ;
    }

    virtual void Characters(const std::string&) {
        ;
    }

    virtual void StackPopNotify(const std::string&) {
        ;
    }

    virtual const std::string& State() const {
        static std::string tag = "global_grid_xy";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(global_grid_xyProcess)
