// GDML
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"

// LCDD
#include "lcdd/schema/region.hh"
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/core/UserRegionInformation.hh"
#include "lcdd/schema/LimitSetType.hh"
#include "lcdd/util/StringUtil.hh"

// Geant4
#include "G4Region.hh"
#include "G4ProductionCuts.hh"

// STL
#include <iostream>
#include <sstream>

/**
 * @brief Creates G4Region objects from region elements.
 */
class regionSubscriber: virtual public SAXSubscriber {
public:
    virtual const SAXComponentObject* Build() const {
        return this;
    }

public:
    regionSubscriber() {
        Subscribe("region");
    }

    virtual void Activate(const SAXObject* object) {
        if (object != 0) {

            LCDDProcessor* proc = LCDDProcessor::instance();

            const region* robj = dynamic_cast<const region*>(object);

            GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
            G4Region* reg = 0;
            if (robj) {
                std::string name = robj->get_name();
                reg = new G4Region(name);

                // compute prod cut
                std::string lunit = robj->get_lunit();
                std::string sval = robj->get_cut();
                sval += "*" + lunit;
                double cut = calc->Eval(sval);

                std::string eunit = robj->get_eunit();
                sval = robj->get_threshold();
                sval += "*" + eunit;
                double threshold = calc->Eval(sval);

                // set production cut
                std::string store_seco = robj->get_storeSecondaries();
                G4ProductionCuts* prod_cuts = new G4ProductionCuts();
                prod_cuts->SetProductionCut(cut);
                reg->SetProductionCuts(prod_cuts);

                // create region info with storeSecondaries flag
                UserRegionInformation* reg_info = new UserRegionInformation();

                // set storeSeco
                reg_info->setStoreSecondaries(StringUtil::toBool(store_seco));

                std::string killTracks = robj->get_killTracks();
                //std::cout << "regionSubscriber.killTracks: " << killTracks << std::endl;
                reg_info->setKillTracks(StringUtil::toBool(killTracks));
                //std::cout << "regInfo.killTracsk: " << reg_info << std::endl;

                // set threshold
                reg_info->setThreshold(threshold);

                // set info in region
                reg->SetUserInformation(reg_info);

                // get content
                const ContentSequence* seq = robj->get_content();

                // get size of content
                size_t count = seq->size();

                // iterate over and process content
                for (size_t i = 0; i < count; i++) {

                    if (seq->content(i).tag == "limitsetref") {

                        LimitSetType::limitsetref* limitsetref = dynamic_cast<LimitSetType::limitsetref*>(seq->content(i).object);

                        G4UserLimits* ulim = dynamic_cast<PhysicsLimitSet*>(proc->getLimitSet(limitsetref->get_ref()));

                        if (ulim) {
#ifdef HAVE_G4REGION_SETUSERLIMITS
                            reg->SetUserLimits( ulim );
                            std::cout << "Set user limits <" << limitsetref->get_ref() << "> on region <" << name << ">" << std::endl;
#else
                            std::cerr
                                    << "WARNING: Ignoring limitsetref on region.  The method G4Region::SetUserLimits is not supported by your Geant4 version."
                                    << std::endl;
#endif
                        } else {
                            std::cerr << "FATAL ERROR: limit element not found - " << limitsetref->get_ref() << std::endl;
                            G4Exception("", "", FatalException, "limitsetref not found.");
                        }
                    } else {
                        std::cerr << "Bad content to region tag: " << seq->content(i).tag << std::endl;
                    }
                }

                // register with processor
                LCDDProcessor::instance()->addRegion(name, reg);
            } else {
                std::cerr << "Failed cast to region!" << std::endl;
            }
        }
    }
};

DECLARE_SUBSCRIBER_FACTORY(regionSubscriber)
