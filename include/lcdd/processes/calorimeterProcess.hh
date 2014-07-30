#ifndef LCDD_PROCESSES_CALORIMETERPROCESS_HH_
#define LCDD_PROCESSES_CALORIMETERPROCESS_HH_ 1

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
 * @brief The SAX process for calorimeter elements.
 * @note Calls SAX processor for SensitiveDetectorTypeProcess parent class.
 */
class calorimeterProcess: public SensitiveDetectorTypeProcess {
public:

    /**
     * Class constructor.
     */
    calorimeterProcess(const ProcessingContext* context = 0);

    /**
     * Class destructor.
     */
    virtual ~calorimeterProcess();

    /**
     * Start element processing.
     */
    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs);

    /**
     * End element processing.
     */
    virtual void EndElement(const std::string&);

    /**
     *
     */
    virtual void Characters(const std::string&);

    /**
     *
     */
    virtual void StackPopNotify(const std::string& name);

    /**
     */
    virtual const std::string& State() const;
};

#endif
