// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/processes/SensitiveDetectorTypeProcess.hh,v 1.5 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_PROCESSES_SENSITIVEDETECTORTYPEPROCESS_HH
#define LCDD_PROCESSES_SENSITIVEDETECTORTYPEPROCESS_HH 1

// LCDD
#include "lcdd/schema/SensitiveDetectorType.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// G4
#include "globals.hh"

// std
#include <iostream>

/**
 @class SensitiveDetectorTypeProcess
 @brief SAX process for elements based on abstract SensitiveDetectorType.
 */
class SensitiveDetectorTypeProcess: public SAXStateProcess {
public:

    SensitiveDetectorTypeProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), _obj(0) {
    }

    virtual ~SensitiveDetectorTypeProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SensitiveDetectorType* sdt = dynamic_cast<SensitiveDetectorType*>(_obj);

        if (sdt) {
            sdt->set_name(attrs.getValue("name"));
            sdt->set_hitsCollectionName(attrs.getValue("hits_collection"));
            sdt->set_ecut(attrs.getValue("ecut"));
            sdt->set_eunit(attrs.getValue("eunit"));
            sdt->set_verbose(attrs.getValue("verbose"));
            sdt->set_endcap_flag(attrs.getValue("endcap_flag"));

            // set the type str for factory build
            sdt->set_type(name);
        } else {
            std::cerr << "SensitiveDetectorTypeProcess::StartElement - cast to SensitiveDetectorType failed!" << std::endl;
        }
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        //std::cout << "SensitiveDetectorTypeProcess::StackPopNotify - " << name << std::endl;

        SAXObject** so = Context()->GetTopObject();
        SensitiveDetectorType* sdt = dynamic_cast<SensitiveDetectorType*>(_obj);

        // Push all content.
        sdt->add_content(name, *so);
    }

protected:
    SAXObject* _obj;

};

#endif
