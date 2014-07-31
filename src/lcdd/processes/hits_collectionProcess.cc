// LCDD
#include "lcdd/processes/hits_collectionProcess.hh"
#include "lcdd/schema/hits_collection.hh"

// GDML
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXComponentFactory.h"

hits_collectionProcess::hits_collectionProcess() :
        SAXStateProcess(0), _obj(0) {
}

hits_collectionProcess::hits_collectionProcess(ProcessingContext* context) :
        SAXStateProcess(context), _obj(0) {
}

hits_collectionProcess::~hits_collectionProcess() {
}

void hits_collectionProcess::StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
    SAXObject** obj = Context()->GetTopObject();
    hits_collection* hitsCollection = new hits_collection;

    hitsCollection->set_name(attrs.getValue("name"));

    _obj = hitsCollection;
    *obj = hitsCollection;
}

void hits_collectionProcess::EndElement(const std::string&) {
}

void hits_collectionProcess::Characters(const std::string&) {
}

void hits_collectionProcess::StackPopNotify(const std::string& name) {
}

const std::string& hits_collectionProcess::State() const {
    static std::string tag = "hits_collection";
    return tag;
}

DECLARE_PROCESS_FACTORY(hits_collectionProcess)
