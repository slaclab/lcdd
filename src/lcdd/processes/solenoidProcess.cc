// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/solenoidProcess.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/schema/solenoid.hh"
#include "lcdd/processes/FieldTypeProcess.hh"

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
 * @brief SAX process for solenoid element.
 */
class solenoidProcess: public FieldTypeProcess {

public:
    solenoidProcess(const ProcessingContext* context = 0) :
            FieldTypeProcess(context) {
    }

    virtual ~solenoidProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        //std::cout << "solenoidProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        solenoid* sol = new solenoid;

        sol->set_innerField(attrs.getValue("inner_field"));
        sol->set_outerField(attrs.getValue("outer_field"));
        sol->set_zmin(attrs.getValue("zmin"));
        sol->set_zmax(attrs.getValue("zmax"));
        sol->set_innerRadius(attrs.getValue("inner_radius"));
        sol->set_outerRadius(attrs.getValue("outer_radius"));

        _obj = sol;
        *obj = sol;

        FieldTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string&) {
        //std::cout << "solenoidProcess::EndElement: " << name << " " << std::endl;
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
        //std::cout << "calorimeterProcess::StackPopNotify: " << name << std::endl;
    }

    virtual const std::string& State() const {
        static std::string tag = "solenoid";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(solenoidProcess)
