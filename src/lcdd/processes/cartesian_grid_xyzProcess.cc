/*
 * cartesian_grid_xyzProcess.cc
 *
 *  Created on: Aug 11, 2014
 *      Author: jeremym
 */

// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "lcdd/schema/cartesian_grid_xyz.hh"

// STL
#include <iostream>

/**
 * @brief The SAX process for cartesian_grid_xyz elements.
 */
class cartesian_grid_xyzProcess: public SAXStateProcess {

public:

    cartesian_grid_xyzProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~cartesian_grid_xyzProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        std::cout << "cartesian_grid_xyzProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        cartesian_grid_xyz* element = new cartesian_grid_xyz;

        element->set_grid_size_x(attrs.getValue("grid_size_x"));
        element->set_grid_size_y(attrs.getValue("grid_size_y"));
        element->set_grid_size_z(attrs.getValue("grid_size_z"));
        element->set_offset_x(attrs.getValue("offset_x"));
        element->set_offset_y(attrs.getValue("offset_y"));
        element->set_offset_z(attrs.getValue("offset_z"));

        std::cout << "grid_size_x: " << element->get_grid_size_x() << std::endl;
        std::cout << "grid_size_y: " << element->get_grid_size_y() << std::endl;
        std::cout << "grid_size_z: " << element->get_grid_size_z() << std::endl;
        std::cout << "offset_x: " << element->get_offset_x() << std::endl;
        std::cout << "offset_y: " << element->get_offset_y() << std::endl;
        std::cout << "offset_z: " << element->get_offset_y() << std::endl;

        m_obj = element;
        *obj = element;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "cartesian_grid_xyz";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(cartesian_grid_xyzProcess)
