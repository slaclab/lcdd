/*
 * cartesian_grid_xzProcess.cc
 *
 *  Created on: Aug 12, 2014
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

// LCDD
#include "lcdd/schema/cartesian_grid_xz.hh"

// STL
#include <iostream>

/**
 * @brief The SAX process for cell_readout_2d elements.
 */
class cartesian_grid_xzProcess: public SAXStateProcess {

public:

    cartesian_grid_xzProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~cartesian_grid_xzProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        std::cout << "cartesian_grid_xyProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        cartesian_grid_xz* element = new cartesian_grid_xz;

        element->set_grid_size_x(attrs.getValue("grid_size_x"));
        element->set_grid_size_z(attrs.getValue("grid_size_z"));
        element->set_offset_x(attrs.getValue("offset_x"));
        element->set_offset_z(attrs.getValue("offset_z"));

        std::cout << "grid_size_x: " << element->get_grid_size_x() << std::endl;
        std::cout << "grid_size_y: " << element->get_grid_size_z() << std::endl;
        std::cout << "offset_x: " << element->get_offset_x() << std::endl;
        std::cout << "offset_y: " << element->get_offset_z() << std::endl;

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
        static std::string tag = "cartesian_grid_xz";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(cartesian_grid_xzProcess)
