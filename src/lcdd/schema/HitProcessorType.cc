// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/schema/HitProcessorType.cc,v 1.3 2013-11-13 23:02:58 jeremy Exp $

#include "lcdd/schema/HitProcessorType.hh"

HitProcessorType::HitProcessorType() {
}

HitProcessorType::~HitProcessorType() {
}

void HitProcessorType::set_type(const std::string& s) {
    _type = s;
}

const std::string& HitProcessorType::get_type() const {
    return _type;
}

void HitProcessorType::add_content(const std::string& tag, SAXObject* saxObject) {
    ContentGroup::ContentItem contentItem = { tag, saxObject };
    _sequence.add_content(contentItem);
}
