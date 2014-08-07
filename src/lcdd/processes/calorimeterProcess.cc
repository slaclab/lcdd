// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/calorimeter.hh"
#include "lcdd/processes/SensitiveDetectorTypeProcess.hh"

// STL
#include <iostream>

/**
 * @brief
 * The SAX process for calorimeter elements
 */
class calorimeterProcess: public SensitiveDetectorTypeProcess {

public:

    calorimeterProcess(const ProcessingContext* context = 0) :
        SensitiveDetectorTypeProcess(context) {
    }

    virtual ~calorimeterProcess() {
    }

    void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();
        calorimeter* cal = new calorimeter;

        cal->set_compare(attrs.getValue("hit_aggregation"));

        _obj = cal;
        *obj = cal;

        // parent type to set name and hitsCollectionName
        SensitiveDetectorTypeProcess::StartElement(name, attrs);
    }

    void EndElement(const std::string&) {
    }

    void Characters(const std::string&) {
    }

    void StackPopNotify(const std::string& name) {
        SensitiveDetectorTypeProcess::StackPopNotify(name);
    }

    const std::string& State() const {
        static std::string tag = "calorimeter";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(calorimeterProcess)
