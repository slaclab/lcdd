// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/processes/volumeExtendedProcess.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $
#ifndef VolumeExtendedProcess_hh
#define VolumeExtendedProcess_hh 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/volume.h"

/**
 * @brief SAX process for the volume element, as extended by LCDD.
 * @note  This is mostly a cut and paste job of GDML's volumeProcess class,
 * as this class does not appear to be extendable.  It is only defined in a cpp
 * file with no include guards!
 */
class volumeExtendedProcess: public SAXStateProcess {
public:
    volumeExtendedProcess(const ProcessingContext* context = 0) :
            SAXStateProcess(context), m_obj(0) {
    }

    virtual ~volumeExtendedProcess() {
    }

    virtual const SAXComponentObject* Build() const {
        return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs) {
        SAXObject** obj = Context()->GetTopObject();

        volume* vo = new volume;

        vo->set_name(attrs.getValue("name"));

        m_obj = vo;
        *obj = vo;
    }

    virtual void EndElement(const std::string&) {
    }

    virtual void Characters(const std::string&) {
    }

    virtual void StackPopNotify(const std::string& name) {
        SAXObject** so = Context()->GetTopObject();
        volume* vobj = dynamic_cast<volume*>(m_obj);
        vobj->add_content(name, *so);
    }

    // The name of the state this object will process
    virtual const std::string& State() const {
        static std::string tag = "volume";
        return tag;
    }

private:
    SAXObject* m_obj;

public:

    static SAXObject* m_volumeSaved;

};

DECLARE_PROCESS_FACTORY(volumeExtendedProcess)

#endif

