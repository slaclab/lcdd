// LCDD
#include "lcdd/schema/region.hh"

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// STL
#include <iostream>

/**
 * @brief SAX process for region element.
 */
class regionProcess: public SAXStateProcess {

public:

    regionProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~regionProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        region* reg = new region;

        reg->set_name(attrs.getValue("name"));
        reg->set_storeSecondaries(attrs.getValue("store_secondaries"));
        reg->set_killTracks(attrs.getValue("kill_tracks"));
        reg->set_cut(attrs.getValue("cut"));
        reg->set_lunit(attrs.getValue("lunit"));
        reg->set_threshold(attrs.getValue("threshold"));
        reg->set_eunit(attrs.getValue("eunit"));

        m_obj = reg;
        *obj = reg;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        SAXObject** so = Context()->GetTopObject();
        region* r = dynamic_cast<region*>(m_obj);
        r->add_content(name, *so);
    }

    virtual const std::string& State() const {
        static std::string tag = "region";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(regionProcess)
