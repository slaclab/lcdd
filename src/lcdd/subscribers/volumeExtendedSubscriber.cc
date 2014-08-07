// LCDD
#include "lcdd/subscribers/volumeExtendedSubscriber.hh"

const SAXComponentObject* volumeExtendedSubscriber::Build() const {
    return this;
}

volumeExtendedSubscriber::volumeExtendedSubscriber() {
    Subscribe("volume");
}

volumeExtendedSubscriber::~volumeExtendedSubscriber() {
}

void volumeExtendedSubscriber::Activate(const SAXObject* object) {
    LCDDProcessor* proc = LCDDProcessor::instance();
    const volume* vobj = 0;
    SensitiveDetector* g4sd = 0;
    G4LogicalVolume* lv;
    int nchildren = 0;

    if (object) {
        vobj = dynamic_cast<const volume*>(object);

        if (vobj) {

            // get LV
            lv = const_cast<G4LogicalVolume*>(GDMLProcessor::GetInstance()->GetLogicalVolume(vobj->get_name()));

            if (lv) {

                // get content
                const ContentSequence* seq = vobj->get_content();

                // get size of content
                size_t count = seq->size();

                // iterate over and process content
                for (size_t i = 0; i < count; i++) {

                    // handle sdref tag
                    if (seq->content(i).tag == "sdref") {

                        SensitiveDetectorType::sdref* sd =
                                dynamic_cast<SensitiveDetectorType::sdref*>(seq->content(
                                        i).object);

                        g4sd = proc->getSensitiveDetector(sd->get_ref());

                        if (g4sd) {

                            if (!g4sd->isValidVolume(lv)) {
                                //G4Exception("FATAL ERROR: The G4LogicalVolume <" + lv->GetName() + "> is not valid for the SD <" + g4sd->GetName() + ">.");
                                G4Exception("", "", FatalException,
                                        "LogVol not valid for the SD");
                            }

                            lv->SetSensitiveDetector(g4sd);
                        } else {
                            G4cerr << "SD not found: " << sd->get_ref() << "."
                                    << G4endl;
                                    G4Exception( "volumeExtendedSubscriber::Activate()", "", FatalException, "Invalid sdref.");
                        }
                    } else if ( seq->content(i).tag == "regionref" ) {
                        // handle regionref

                        // get regionref object
                        RegionType::regionref* regref = dynamic_cast<RegionType::regionref*> ( seq->content(i).object );

                        // get region from store
                        G4Region* reg = dynamic_cast<G4Region*> ( proc->getRegion( regref->get_ref() ) );

                        // add LV to region
                        if ( reg ) {
                            reg->AddRootLogicalVolume( lv );
                        } else {
                            G4cerr << "Failed to fetch and/or cast to region: " << regref->get_ref() << G4endl;
                            G4Exception("volumeExtendedSubscriber::Activate()", "", FatalException, "Invalid regionref.");
                        }
                    } else if ( seq->content(i).tag == "limitsetref" ) {
                        // handle limitsetref

                        LimitSetType::limitsetref* limitsetref = dynamic_cast<LimitSetType::limitsetref*> ( seq->content(i).object );

                        G4UserLimits* ulim = dynamic_cast<PhysicsLimitSet*> ( proc->getLimitSet( limitsetref->get_ref() ) );

                        if ( ulim ) {
                            lv->SetUserLimits( ulim );
                            std::cout << "Set user limits <" << limitsetref->get_ref() << "> on logical volume <" << lv->GetName() << ">" << std::endl;
                        } else {
                            std::cerr << "FATAL ERROR: limit element not found - " << limitsetref->get_ref() << std::endl;
                            G4Exception("", "", FatalException, "limitsetref not found.");
                        }
                    } else if ( seq->content(i).tag == "visref" ) {
                        // handle visref

                        //std::cout << "handling visref" << std::endl;

                        VisType::visref* visref = dynamic_cast<VisType::visref*> ( seq->content(i).object );

                        G4VisAttributes* vis = dynamic_cast<G4VisAttributes*> ( proc->getVisAttributes( visref->get_ref() ) );

                        if ( vis ) {
                            //std::cout << "assigning vis: " << visref->get_ref() << std::endl;
                            lv->SetVisAttributes( vis );
                        } else {
                            std::cerr << "FATAL ERROR: vis element not found - " << visref->get_ref() << std::endl;
                            G4Exception("", "", FatalException, "vis element not found.");
                        }
                    }
                    if ( seq->content(i).tag == "physvol" ) {
                        // handle physvols to look for physvolids

                        ++nchildren;

                        // get physvol content sequence
                        physvol* pv = dynamic_cast<physvol*>( seq->content(i).object );
                        const ContentSequence* pv_seq = pv->get_content();
                        size_t ccount = pv_seq->size();

                        // iterate over physvol content
                        for ( size_t pvidx = 0; pvidx < ccount; pvidx++ ) {

                            // found "choice" tag?
                            if( pv_seq->content(pvidx).tag == "choice" ) {

                                const ContentChoice* pv_choice = dynamic_cast<const ContentChoice*>( pv_seq->content(pvidx).object );

                                // found a physvolid?
                                if ( pv_choice->content().tag == "physvolid" ) {

                                    // add the physvolid...

                                    physvolidElem* pvid_elem =
                                            dynamic_cast<physvolidElem*>( pv_choice->content().object );

                                    if ( pvid_elem == 0 ) {
                                        G4Exception("", "", FatalException, "Failed cast to physvolidElem.");
                                    }

                                    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

                                    std::string strID = pvid_elem->get_value();
                                    std::string fld = pvid_elem->get_field_name();

                                    int intID = (int)calc->Eval( strID );

                                    PhysVolId pvid(intID, fld);

                                    // assign physvolid to lv's child by the in-order idx
                                    IdManager::instance()->addPhysVolId(
                                            lv,// LV mom
                                            nchildren - 1,// child idx in mom
                                            pvid );// PhysVolId
                                }
                            }
                        }
                    }
                }
            } else {
                G4Exception("", "", FatalException, "Failed cast to G4LogicalVolume.");
            }
        } else {
            G4Exception("", "", FatalException, "Failed cast to volume.");
        }
    }
}
