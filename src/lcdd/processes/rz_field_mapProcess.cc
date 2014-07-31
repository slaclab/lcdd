// LCDD
#include "lcdd/processes/FieldMapTypeProcess.hh"
#include "lcdd/schema/rz_field_map.hh"

// Geant4
#include "globals.hh"

// STL
#include <iostream>

/**
 * @brief Processor for rz_field_map elements.
 */
class rz_field_mapProcess: public FieldMapTypeProcess {
public:
    rz_field_mapProcess(const ProcessingContext* context = 0) :
            FieldMapTypeProcess(context) {
    }

    virtual ~rz_field_mapProcess() {
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        //    std::cout << "rz_field_mapProcess::StartElement - " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        rz_field_map* rzmap = new rz_field_map;

        /* set attributes */
        rzmap->set_num_bins_r(attrs.getValue("num_bins_r"));
        rzmap->set_grid_size_r(attrs.getValue("grid_size_r"));
        rzmap->set_num_bins_z(attrs.getValue("num_bins_z"));
        rzmap->set_grid_size_z(attrs.getValue("grid_size_z"));

        /* Top-level caller needs to setup the SAXObject references. */
        _obj = rzmap;
        *obj = rzmap;

        /* Call next process UP in inheritance chain, after the SAXObject is set. */
        FieldMapTypeProcess::StartElement(name, attrs);
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        //    std::cout << "rz_field_mapProcess::StackPopNotify" << std::endl;

        if (name != "rzB") {
            std::cerr << name << " is not a valid child element for rz_field_map." << std::endl;
            exit(1);
        }

        FieldMapTypeProcess::StackPopNotify(name);
    }

    virtual const std::string& State() const {
        static std::string tag = "rz_field_map";
        return tag;
    }
};

DECLARE_PROCESS_FACTORY(rz_field_mapProcess)
