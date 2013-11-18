// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/hit_processorProcess.cc,v 1.3 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/processes/hit_processorProcess.hh"
#include "lcdd/schema/hit_processor.hh"

// GDML
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXComponentFactory.h"

hit_processorProcess::hit_processorProcess() :
        SAXStateProcess(0), _obj(0) {
}

hit_processorProcess::hit_processorProcess(ProcessingContext* context) :
        SAXStateProcess(context), _obj(0) {

}

hit_processorProcess::~hit_processorProcess() {

}

void hit_processorProcess::StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
    SAXObject** obj = Context()->GetTopObject();
    hit_processor* hitProcessor = new hit_processor;

    hitProcessor->set_type(attrs.getValue("type"));

    _obj = hitProcessor;
    *obj = hitProcessor;
}

void hit_processorProcess::EndElement(const std::string&) {
}

void hit_processorProcess::Characters(const std::string&) {
}

void hit_processorProcess::StackPopNotify(const std::string& name) {
    SAXObject** so = Context()->GetTopObject();
    HitProcessorType* hitProcessorType = dynamic_cast<HitProcessorType*>(_obj);

    // Push child elements into type object.
    hitProcessorType->add_content(name, *so);
}

const std::string& hit_processorProcess::State() const {
    static std::string tag = "hit_processor";
    return tag;
}

DECLARE_PROCESS_FACTORY(hit_processorProcess)
