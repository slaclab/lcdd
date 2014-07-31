// LCDD
#include "lcdd/schema/grid_xyz.hh"

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
 * @brief SAX process for grid_xyz element.
 */
class grid_xyzProcess: public SAXStateProcess {

public:

    grid_xyzProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~grid_xyzProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        //std::cout << "grid_xyzProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        grid_xyz* np = new grid_xyz;

        np->set_lunit(attrs.getValue("lunit"));

        np->set_gridSizeX(attrs.getValue("grid_size_x"));
        np->set_gridSizeY(attrs.getValue("grid_size_y"));
        np->set_gridSizeZ(attrs.getValue("grid_size_z"));

        m_obj = np;
        *obj = np;
    }

    virtual void EndElement(const std::string&) {
        //std::cout << "PROCESS::END OF TAG  : " << name << " " << std::endl;
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
        //std::cout << "PROCESS::NOTIFIED AFTER THE TAG: " << name << std::endl;
    }

    virtual const std::string& State() const {
        static std::string tag = "grid_xyz";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(grid_xyzProcess)
