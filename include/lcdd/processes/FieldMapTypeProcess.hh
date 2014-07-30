#ifndef LCDD_PROCESSES_FIELDMAPTYPEPROCESS_HH_
#define LCDD_PROCESSES_FIELDMAPTYPEPROCESS_HH_ 1

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/FieldMapType.hh"
#include "lcdd/schema/FieldType.hh"
#include "lcdd/processes/FieldTypeProcess.hh"

// STL
#include <iostream>

/**
 * @brief Generic SAX process for field maps.
 * @note This class adds generic content using StackPopNotify.
 */
class FieldMapTypeProcess: public FieldTypeProcess {
public:

    /**
     * Class constructor.
     */
    FieldMapTypeProcess(const ProcessingContext* context = 0) :
            FieldTypeProcess(context) {
    }

    /**
     * Class destructor.
     */
    virtual ~FieldMapTypeProcess() {
    }

    /**
     *
     */
    virtual const SAXComponentObject* Build() const {
        return this;
    }

    /*
     * NO-OP.  Just call up the inheritance chain to FieldTypeProcess.
     */
    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        //    std::cout << "FieldMapTypeProcess::StartElement - " << name << std::endl;
        FieldTypeProcess::StartElement(name, attrs);
    }

    /**
     *
     */
    virtual void EndElement(const std::string&) {
    }

    /**
     *
     */
    virtual void Characters(const std::string&) {
    }

    /**
     *
     */
    virtual void StackPopNotify(const std::string& name) {
        //    std::cout << "FieldMapTypeProcess::StackPopNotify" << std::endl;
        SAXObject** so = Context()->GetTopObject();
        FieldMapType* fmap = dynamic_cast<FieldMapType*>(_obj);
        fmap->add_content(name, *so);
    }
};

#endif
