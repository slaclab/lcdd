#include "lcdd/detectors/SensitiveDetectorFactory.hh"

// LCDD
#include "lcdd/id/IdComparator.hh"
#include "lcdd/util/StringUtil.hh"
#include "lcdd/detectors/PositionComparator.hh"
#include "lcdd/detectors/HitProcessorManager.hh"
#include "lcdd/detectors/LegacyCalorimeterHitProcessor.hh"
#include "lcdd/detectors/BasicTrackerHitProcessor.hh"
#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"
#include "lcdd/schema/hit_processor.hh"
#include "lcdd/schema/hits_collection.hh"

SensitiveDetector* SensitiveDetectorFactory::createSensitiveDetector(const SAXObject* object) {
    const SensitiveDetectorType* sensitiveDetectorType = dynamic_cast<const SensitiveDetectorType*>(object);
    SensitiveDetector* sensitiveDetector = 0;
    IdSpec* idspec = 0;
    std::vector<HitProcessor*> hitProcessors;
    std::vector<std::string> hitProcessorNames;
    std::vector<G4String> hitsCollections;

    // The SAXObject must extend SensitiveDetectorType.
    if (sensitiveDetectorType) {

        // Get the SensitiveDetector's basic type string.
        std::string sensitiveDetectorTypeName = sensitiveDetectorType->get_type();

        // Process element content for objects that need to be created before the SD.
        ContentSequence* seq = const_cast<ContentSequence*>(sensitiveDetectorType->get_content());
        size_t count = seq->size();
        for (size_t i = 0; i < count; i++) {

            std::string childTag = seq->content(i).tag;

            // Process idspecref child tag.
            if (childTag == "idspecref") {

                // Cast the SAXObject to appropriate element type.
                IdSpecType::idspecref* ref = dynamic_cast<IdSpecType::idspecref*>(seq->content(i).object);

                // Get the idspec pointed to by the idspecref.
                idspec = IdManager::instance()->getIdSpec(ref->get_ref());

                // Check if the IdSpec exists.
                if (idspec == 0) {
                    G4cerr << "IdSpec <" << ref->get_ref() << "> referenced by detector <" << sensitiveDetectorType->get_name() << "> does not exist."
                            << G4endl;
                    G4Exception("", "", FatalException, "IdSpec does not exist.");
                }

                // Process hit_processor child tag.
            } else if (childTag == "hit_processor") {

                // Cast object to appropriate element type.
                const hit_processor* hitProcessor = dynamic_cast<const hit_processor*>(seq->content(i).object);

                // Push type name of HitProcessor onto list to be created later once SD is available.
                hitProcessorNames.push_back(hitProcessor->get_type());

                // Process hits_collection child tag.
            } else if (childTag == "hits_collection") {

                // Cast object to appropriate element type.
                const hits_collection* hitsCollection = dynamic_cast<const hits_collection*>(seq->content(i).object);

                // Get the name of the hits collection.
                const std::string& name = hitsCollection->get_name();

                // Add hits collection to the list.
                hitsCollections.push_back(name);
            }
        }

        // This is for backward compatibility when hits collection is specified as an attribute value
        // on the detector's XML element.
        std::string hitsCollectionName = sensitiveDetectorType->get_hitsCollectionName();
        if (hitsCollectionName != "") {
            hitsCollections.push_back(sensitiveDetectorType->get_hitsCollectionName());
        }

        // If no hits collections were added then make a default HitsCollection with the name of the SD.
        if (hitsCollections.size() == 0) {
            hitsCollections.push_back(sensitiveDetectorType->get_name());
        }

        // Create the SD object based on its type of calorimeter or tracker.
        if (sensitiveDetectorTypeName == "calorimeter") {
            // Create calorimeter SD.
            sensitiveDetector = createCalorimeter(object, hitsCollections);
        } else if (sensitiveDetectorTypeName == "tracker") {
            // Create tracker SD.
            sensitiveDetector = createTracker(object, hitsCollections);
        } else {
            // Type is not recognized.  This shouldn't happen!
            G4cerr << "Invalid sensitive detector type: " << sensitiveDetectorTypeName << G4endl;
            G4Exception("", "", FatalException, "Unknown sensitive detector type.");
        }

        // Set the base attributes.
        sensitiveDetector->setEcut(SensitiveDetectorFactory::computeEcut(sensitiveDetectorType));
        sensitiveDetector->setVerbose(SensitiveDetectorFactory::convertVerbose(sensitiveDetectorType));
        sensitiveDetector->setEndcapFlag(StringUtil::toBool(sensitiveDetectorType->get_endcap_flag()));

        // Set the IdSpec.
        sensitiveDetector->setIdSpec(idspec);

        // Create HitProcessors from list of type names.
        for (std::vector<std::string>::iterator it = hitProcessorNames.begin(); it != hitProcessorNames.end(); it++) {
            std::string type = (*it);
            HitProcessorFactory* hitProcessorFactory = HitProcessorManager::instance()->getFactory(type);
            if (hitProcessorFactory == 0) {
                std::cerr << "HitProcessorFactory was not found for type: " << type << std::endl;
                G4Exception("", "", FatalException, "HitProcessor not found");
            }
            HitProcessor* processor = hitProcessorFactory->createHitProcessor(sensitiveDetector);

            //std::cout << "create hits processor: " << type << std::endl;

            // Add the HitProcessor to the list.
            hitProcessors.push_back(processor);
        }

        // Add the HitProcessors from the list.
        if (hitProcessors.size() > 0) {
            // Add HitProcessors created from XML if they were listed explicitly as child elements.
            sensitiveDetector->addHitProcessors(hitProcessors);
        } else {
            // Need to add default HitProcessors because none were specified in the detector's XML.
            if (sensitiveDetectorTypeName == "tracker") {
                // Add the default TrackerHitProcessor.
                sensitiveDetector->addHitProcessor(
                        HitProcessorManager::instance()->getFactory("BasicTrackerHitProcessor")->createHitProcessor(sensitiveDetector));
            } else if (sensitiveDetectorTypeName == "calorimeter") {
                // Add the default CalorimeterHitProcessor.
                sensitiveDetector->addHitProcessor(
                        HitProcessorManager::instance()->getFactory("LegacyCalorimeterHitProcessor")->createHitProcessor(sensitiveDetector));
            }
        }

        // Register the SensitiveDetector with the LCDDProcessor.
        std::string sensitiveDetectorName = sensitiveDetector->GetName();
        //std::cout << "adding sensitive detector: " << sensitiveDetectorName << std::endl;
        //std::cout << "  HCs: ";
        //for (std::vector<G4String>::iterator it = hitsCollections.begin(); it != hitsCollections.end(); it++) {
        //	std::cout << (*it) << " ";
        //}
        //std::cout << std::endl;
        LCDDProcessor::instance()->addSensitiveDetector(sensitiveDetectorName, sensitiveDetector);
    } else {
        // This should never really happen.
        G4Exception("", "", FatalException, "Failed cast to SensitiveDetectorType.");
    }

    return sensitiveDetector;
}

SensitiveDetector* SensitiveDetectorFactory::createCalorimeter(const SAXObject* object, const std::vector<G4String>& hitsCollections) {
    const SensitiveDetectorType* sensitiveDetectorType = dynamic_cast<const SensitiveDetectorType*>(object);
    Segmentation* segmentation = 0;

    // Create the segmentation child object prior to the calorimeter.
    ContentSequence* seq = const_cast<ContentSequence*>(sensitiveDetectorType->get_content());
    size_t count = seq->size();
    bool fnd_seg = false;
    for (size_t i = 0; i < count; i++) {
        std::string child_tag = seq->content(i).tag;
        const ContentGroup::ContentItem& segitem = seq->content(i);
        // Create segmentation using factory.
        if (isSegmentationTag(child_tag)) {
            segmentation = SegmentationFactory::createSegmentation(segitem.object, segitem.tag);
            fnd_seg = true;
            break;
        }
    }

    // Get the calorimeter XML object.
    const calorimeter* cal = dynamic_cast<const calorimeter*>(object);

    // Create the calorimeter SD.
    return new CalorimeterSD(sensitiveDetectorType->get_name(), hitsCollections, segmentation);
}

TrackerSD* SensitiveDetectorFactory::createTracker(const SAXObject* object, const std::vector<G4String>& hitsCollections) {
    // Cast the SAXObject to tracker element.
    const tracker* trackerElement = dynamic_cast<const tracker*>(object);

    // Create the tracker.
    TrackerSD* sd = new TrackerSD(trackerElement->get_name(), hitsCollections);

    return sd;
}

double SensitiveDetectorFactory::computeEcut(const SensitiveDetectorType* sdt) {
    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
    std::string sval = sdt->get_ecut();
    sval += "*" + sdt->get_eunit();
    double ecut = calc->Eval(sval);
    return ecut;
}

int SensitiveDetectorFactory::convertVerbose(const SensitiveDetectorType* sdt) {
    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
    std::string sval = sdt->get_verbose();
    int verbose = (int) calc->Eval(sval);
    return verbose;
}

bool SensitiveDetectorFactory::isSegmentationTag(const std::string& s) {
    // FIXME This should automatically know all segmentation types somehow.
    //       Can this be read from the schema?
    //       http://xerces-c.sourcearchive.com/documentation/3.1.1-1/SchemaGrammar_8hpp_source.html
    return (s == "projective_cylinder" || s == "grid_xyz" || s == "global_grid_xy" || s == "nonprojective_cylinder" || s == "projective_zplane"
            || s == "cell_readout_2d");
}
