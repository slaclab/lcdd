// LCDD
#include "lcdd/schema/hit_processor.hh"

// GDML
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXComponentFactory.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObject.h"

/**
 * The SAX process for hit_processor elements.
 */
class hit_processorProcess: public SAXStateProcess {

    public:

    hit_processorProcess() :
        SAXStateProcess(0), _obj(0) {
    }

    hit_processorProcess(ProcessingContext* context) :
        SAXStateProcess(context), _obj(0) {
    }

    virtual ~hit_processorProcess() {
    }

    void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();
        hit_processor* hitProcessor = new hit_processor;

        hitProcessor->set_type(attrs.getValue("type"));
        hitProcessor->set_collection_name(attrs.getValue("collection_name"));

        _obj = hitProcessor;
        *obj = hitProcessor;
    }

    void EndElement(const std::string&) {
    }

    void Characters(const std::string&) {
    }

    // TODO: Add this back if there are child elements added to HitsProcessor XML type.
    void StackPopNotify(const std::string& name) {
    //    SAXObject** so = Context()->GetTopObject();
    //    HitProcessorType* hitProcessorType = dynamic_cast<HitProcessorType*>(_obj);
        // Push child elements into type object.
    //    hitProcessorType->add_content(name, *so);
    }

    const std::string& State() const {
        static std::string tag = "hit_processor";
        return tag;
    }

    private:
        SAXObject* _obj;
};

DECLARE_PROCESS_FACTORY(hit_processorProcess)
