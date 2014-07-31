// GDML
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// LCDD
#include "lcdd/schema/cell_readout_2d.hh"

// STL
#include <iostream>

/**
 * @brief The SAX process for cell_readout_2d elements.
 */
class cell_readout_2dProcess: public SAXStateProcess {

public:

    cell_readout_2dProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~cell_readout_2dProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    virtual void StartElement(const std::string& name, const ASCIIAttributeList& attrs) {
        std::cout << "cell_readout_2dProcess::StartElement: " << name << std::endl;

        SAXObject** obj = Context()->GetTopObject();

        cell_readout_2d* np = new cell_readout_2d;

        np->setLengthUnit(attrs.getValue("lunit"));

        np->setCellSizeX(attrs.getValue("cell_size_x"));
        np->setCellSizeY(attrs.getValue("cell_size_y"));

        m_obj = np;
        *obj = np;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string&) {
    }

    virtual const std::string& State() const {
        static std::string tag = "cell_readout_2d";
        return tag;
    }

private:

    SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(cell_readout_2dProcess)
