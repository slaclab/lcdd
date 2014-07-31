// LCDD
#include "lcdd/processes/FieldMapTypeProcess.hh"
#include "lcdd/schema/field_map_3d.hh"

// STL
#include <iostream>

// Geant4
#include "globals.hh"

/**
 * @brief The SAX process for field_map_3d elements.
 */
class field_map_3dProcess: public FieldMapTypeProcess {

public:

    field_map_3dProcess(const ProcessingContext* context = 0) :
            FieldMapTypeProcess(context) {
    }

    virtual ~field_map_3dProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        // Create schema object.
        field_map_3d* fmap = new field_map_3d;

        // Set input values from XML.
        fmap->set_filename(attrs.getValue("filename"));
        fmap->set_xoffset(attrs.getValue("xoffset"));
        fmap->set_yoffset(attrs.getValue("yoffset"));
        fmap->set_zoffset(attrs.getValue("zoffset"));

        // This is the top-level caller, so it needs to setup the SAXObject references.
        _obj = fmap;
        *obj = fmap;

        // Call next process UP in inheritance chain, after the SAXObject is set.
        FieldMapTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        //std::cout << "field_map_3d::StackPopNotify" << std::endl;
        FieldMapTypeProcess::StackPopNotify(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "field_map_3d";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(field_map_3dProcess)
