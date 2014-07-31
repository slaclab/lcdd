// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/geant4/LCDDHeaderRecord.hh"
#include "lcdd/schema/header.hh"
#include "lcdd/schema/detector.hh"
#include "lcdd/schema/generator.hh"
#include "lcdd/schema/comment.hh"
#include "lcdd/schema/author.hh"

// STL
#include <iostream>

/**
 * @brief Creates LCDDHeaderRecord objects from header elements.
 */
class headerSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    headerSubscriber() {
        Subscribe("header");
    }

    virtual ~headerSubscriber() {
    }

    virtual void Activate(const SAXObject* object) {
        LCDDProcessor* proc = LCDDProcessor::instance();
        const header* obj = dynamic_cast<const header*>(object);
        LCDDHeaderRecord* hdr = new LCDDHeaderRecord();

        // handle child element content
        ContentSequence* seq = const_cast<ContentSequence*>(obj->get_content());
        size_t count = seq->size();
        for (size_t i = 0; i < count; i++) {

            const ContentGroup::ContentItem& citem = seq->content(i);
            const std::string& tag = citem.tag;
            SAXObject* cobj = citem.object;

            if (tag == "detector") {

                const detector* d = dynamic_cast<detector*>(cobj);

                hdr->setDetectorName(d->get_name());
                hdr->setDetectorVersion(d->get_version());
                hdr->setDetectorUrl(d->get_url());
            } else if (tag == "generator") {

                const generator* g = dynamic_cast<generator*>(cobj);

                hdr->setGeneratorName(g->get_name());
                hdr->setGeneratorVersion(g->get_version());
                hdr->setGeneratorFile(g->get_file());
                hdr->setGeneratorChecksum(g->get_checksum());
            } else if (tag == "author") {

                const author* a = dynamic_cast<author*>(cobj);

                hdr->setAuthorName(a->get_name());
                hdr->setAuthorEmail(a->get_email());

            } else if (tag == "comment") {

                const comment* c = dynamic_cast<comment*>(cobj);
                hdr->setComment(c->get_comment());
            } else {
                std::cerr << "Unknown content for header element." << std::endl;
            }
        }

        // set header in LCDDProc
        proc->setHeader(hdr);

        // print header
        hdr->printOut(std::cout);

        //delete object;
    }

};

DECLARE_SUBSCRIBER_FACTORY(headerSubscriber)
