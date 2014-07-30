#ifndef LCDD_PROCESSES_HIT_PROCESSORPROCESS_HH_
#define LCDD_PROCESSES_HIT_PROCESSORPROCESS_HH_ 1

// GDML
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObject.h"

class hit_processorProcess: public SAXStateProcess {

public:

    hit_processorProcess();

    hit_processorProcess(ProcessingContext* context);

    virtual ~hit_processorProcess();

    /**
     * Start element processing.
     */
    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs);

    /**
     * End element processing.
     */
    virtual void EndElement(const std::string&);

    /**
     * Process element character content.
     */
    virtual void Characters(const std::string&);

    virtual void StackPopNotify(const std::string& name);

    virtual const std::string& State() const;

private:

    SAXObject* _obj;

};

#endif
