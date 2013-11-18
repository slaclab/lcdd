// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/processes/hit_processorProcess.hh,v 1.3 2013-11-14 00:47:21 jeremy Exp $

#ifndef LCDD_PROCESSES_HITPROCESSORPROCESS_HH
#define LCDD_PROCESSES_HITPROCESSORPROCESS_HH 1

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
