#ifndef LCDD_PROCESSES_FIELDTYPEPROCESS_HH_
#define LCDD_PROCESSES_FIELDTYPEPROCESS_HH_ 1

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/FieldType.hh"

// STL
#include <iostream>

/**
 * @brief Generic SAX process for fields.
 * @note This class sets name and units for a field.
 */
class FieldTypeProcess: public SAXStateProcess {
public:

    /**
     *
     */
    FieldTypeProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), _obj(0) {
    }

    /**
     *
     */
    virtual ~FieldTypeProcess() {
    }

    /**
     *
     */
    virtual const SAXComponentObject* Build() const {
        return this;
    }

    /**
     *
     */
    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "FieldTypeProcess::StartElement: " << name << std::endl;

        FieldType* fld = dynamic_cast<FieldType*>(_obj);

        if (fld) {

            fld->set_name(attrs.getValue("name"));
            fld->set_funit(attrs.getValue("funit"));
            fld->set_lunit(attrs.getValue("lunit"));

            //std::cout << "name: " << fld->get_name() << std::endl;
        } else {
            std::cerr << "Failed cast to FieldType." << std::endl;
        }
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
    virtual void StackPopNotify(const std::string&) {
        //std::cout << "FieldTypeProcess::StackPopNotify" << std::endl;
    }

protected:
    SAXObject* _obj;
};

#endif
