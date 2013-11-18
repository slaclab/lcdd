// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/calorimeterProcess.cc,v 1.3 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/processes/calorimeterProcess.hh"

calorimeterProcess::calorimeterProcess(const ProcessingContext* context) :
        SensitiveDetectorTypeProcess(context) {
}

calorimeterProcess::~calorimeterProcess() {
}

void calorimeterProcess::StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
    SAXObject** obj = Context()->GetTopObject();
    calorimeter* cal = new calorimeter;

    cal->set_compare(attrs.getValue("hit_aggregation"));

    _obj = cal;
    *obj = cal;

    // parent type to set name and hitsCollectionName
    SensitiveDetectorTypeProcess::StartElement(name, attrs);
}

void calorimeterProcess::EndElement(const std::string&) {
}

void calorimeterProcess::Characters(const std::string&) {
}

void calorimeterProcess::StackPopNotify(const std::string& name) {
    SensitiveDetectorTypeProcess::StackPopNotify(name);
}

const std::string& calorimeterProcess::State() const {
    static std::string tag = "calorimeter";
    return tag;
}

DECLARE_PROCESS_FACTORY(calorimeterProcess)
