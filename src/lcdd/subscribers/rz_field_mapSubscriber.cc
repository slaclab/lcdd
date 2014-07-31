// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/rz_field_map.hh"
#include "lcdd/schema/rzb.hh"
#include "lcdd/bfield/RZFieldMap.hh"

/**
 * @brief Creates RZFieldMap objects from rz_field_map elements.
 */
class rz_field_mapSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    rz_field_mapSubscriber() {
        Subscribe("rz_field_map");
    }

    virtual ~rz_field_mapSubscriber() {
    }

    /** Instantiates a G4RZFieldMap object into Geant4 runtime. */
    virtual void Activate(const SAXObject* object) {
        //std::cout << "rz_field_mapSubscriber" << std::endl;

        if (object != 0) {

            GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

            const rz_field_map* obj = dynamic_cast<const rz_field_map*>(object);

            if (obj) {
                std::string lunit = obj->get_lunit();
                std::string funit = obj->get_funit();
                std::string name = obj->get_name();

                int numBinsR, numBinsZ;
                double gridSizeR, gridSizeZ;

                std::string sval = obj->get_num_bins_r();
                numBinsR = (int) calc->Eval(sval);

                sval = obj->get_num_bins_z();
                numBinsZ = (int) calc->Eval(sval);

                sval = obj->get_grid_size_r();
                sval += "*" + lunit;
                gridSizeR = calc->Eval(sval);

                sval = obj->get_grid_size_z();
                sval += "*" + lunit;
                gridSizeZ = calc->Eval(sval);

                /* Make list of RZB rows from content. */
                const ContentSequence* seq = obj->get_content();
                size_t count = seq->size();
                std::vector<RZBData> fieldData;

                for (size_t i = 0; i < count; i++) {

                    if (seq->content(i).tag == "rzB") {

                        rzb* row = dynamic_cast<rzb*>(seq->content(i).object);

                        if (row != 0) {

                            std::string sr = row->get_r();
                            std::string sz = row->get_z();
                            std::string sBr = row->get_Br();
                            std::string sBz = row->get_Bz();

                            std::string sval = sr;
                            sval += "*" + lunit;
                            double r = calc->Eval(sval);

                            sval = sz;
                            sval += "*" + lunit;
                            double z = calc->Eval(sval);

                            sval = sBr;
                            sval += "*" + funit;
                            double Br = calc->Eval(sval);

                            sval = sBz;
                            sval += "*" + funit;
                            double Bz = calc->Eval(sval);

                            fieldData.push_back(RZBData(r, z, Br, Bz));
                        } else {
                            G4Exception("", "", FatalException, "Failed cast to rzB.");
                        }
                    } else {
                        G4cerr << "WARNING: Ignoring unknown element " << seq->content(i).tag << "." << std::endl;
                    }
                }

                RZFieldMap* fmap = new RZFieldMap(numBinsR, numBinsZ, gridSizeR, gridSizeZ, fieldData);
                LCDDProcessor::instance()->addMagneticField(name, fmap);
            } else {
                G4Exception("", "", FatalException, "Failed cast to rz_field_map.");
            }
        } else {
            G4Exception("", "", FatalException, "SAXObject is null.");
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(rz_field_mapSubscriber)
