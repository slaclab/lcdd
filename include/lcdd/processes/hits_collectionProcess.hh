#ifndef LCDD_PROCESSES_HITS_COLLECTIONPROCESS_HH_
#define LCDD_PROCESSES_HITS_COLLECTIONPROCESS_HH_ 1

// GDML
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObject.h"

class hits_collectionProcess: public SAXStateProcess {

public:

    hits_collectionProcess();

    hits_collectionProcess(ProcessingContext* context);

    virtual ~hits_collectionProcess();

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
