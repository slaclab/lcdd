#include "lcdd/detectors/SensitiveDetectorFactory.hh"

// LCDD
#include "lcdd/id/IdComparator.hh"
#include "lcdd/util/StringUtil.hh"
#include "lcdd/detectors/PositionComparator.hh"
#include "lcdd/detectors/HitProcessorManager.hh"
#include "lcdd/detectors/BasicCalorimeterHitProcessor.hh"
#include "lcdd/detectors/BasicTrackerHitProcessor.hh"
#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"
#include "lcdd/schema/hit_processor.hh"
#include "lcdd/schema/cartesian_grid_xy.hh"
#include "lcdd/schema/cartesian_grid_xz.hh"
#include "lcdd/schema/cartesian_grid_xyz.hh"
#include "lcdd/schema/projective_cylinder.hh"

// GDML
#include "G4Evaluator/GDMLExpressionEvaluator.h"

// DD4hep
#include "DDSegmentation/CartesianGridXY.h"
#include "DDSegmentation/CartesianGridXZ.h"
#include "DDSegmentation/CartesianGridXYZ.h"
#include "DDSegmentation/ProjectiveCylinder.h"

using DD4hep::DDSegmentation::CartesianGridXY;
using DD4hep::DDSegmentation::CartesianGridXZ;
using DD4hep::DDSegmentation::CartesianGridXYZ;
using DD4hep::DDSegmentation::ProjectiveCylinder;

#include <algorithm>
#include <exception>

SensitiveDetector* SensitiveDetectorFactory::createSensitiveDetector(const SAXObject* object) {

    const SensitiveDetectorType* sensitiveDetectorType = dynamic_cast<const SensitiveDetectorType*>(object);
    SensitiveDetector* sensitiveDetector = 0;
    IdSpec* idspec = 0;
    std::vector<HitProcessor*> hitProcessors;
    std::vector<G4String> hitsCollections;

    // The SAXObject must extend SensitiveDetectorType.
    if (sensitiveDetectorType) {

        // Get the SensitiveDetector's basic type string.
        std::string sensitiveDetectorTypeName = sensitiveDetectorType->get_type();

        // If there is a collection name on the SD itself, add it to the list.
        std::string hitsCollectionName = sensitiveDetectorType->get_hitsCollectionName();
        if (hitsCollectionName != "") {
            hitsCollections.push_back(sensitiveDetectorType->get_hitsCollectionName());
        }

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
                const hit_processor* element = dynamic_cast<const hit_processor*>(seq->content(i).object);

                // Create the HitProcessor.
                HitProcessorFactory* hitProcessorFactory = HitProcessorManager::instance()->getFactory(element->get_type());
                if (hitProcessorFactory == NULL)
                    G4Exception("", "", FatalException, "HitProcessorFactory was not found.");
                HitProcessor* hitProcessor = hitProcessorFactory->createHitProcessor();

                // Set the hits collection name (optional).
                G4String hitsCollection = element->get_collection_name();
                if (hitsCollection != "") {
                    G4cout << "set collection name on HitProcessor: " << hitsCollection << G4endl;
                    hitProcessor->setCollectionName(hitsCollection);
                }

                // Add hits collection name to the list unless it is already defined by the SD.
                if (hitsCollection != "") {
                    if (std::find(hitsCollections.begin(), hitsCollections.end(), hitsCollection) == hitsCollections.end()) {
                        hitsCollections.push_back(hitsCollection);
                    }
                }

                // Add the HitsProcessor to the list for the SD.
                hitProcessors.push_back(hitProcessor);
            }
        }

        // Add default HitProcessor if none was provided explicitly in the SD's XML element.
        if (hitProcessors.size() == 0) {
            if (sensitiveDetectorTypeName == "tracker") {
                hitProcessors.push_back(HitProcessorManager::instance()->getFactory("BasicTrackerHitProcessor")->createHitProcessor());
            } else if (sensitiveDetectorTypeName == "calorimeter") {
                hitProcessors.push_back(HitProcessorManager::instance()->getFactory("BasicCalorimeterHitProcessor")->createHitProcessor());
            }
        }

        // If no hits collection names were provided explicitly, then make a default one from the name of the SD.
        if (hitsCollections.size() == 0) {
            hitsCollections.push_back(sensitiveDetectorType->get_name());
        }

        // Create the SD object based on its type of calorimeter or tracker.
        if (sensitiveDetectorTypeName == "calorimeter") {
            // Create the CalorimeterSD with its hits collection names.
            sensitiveDetector = createCalorimeter(object, hitsCollections);
        } else if (sensitiveDetectorTypeName == "tracker") {
            // Create the TrackerSD with its hits collection names.
            sensitiveDetector = createTracker(object, hitsCollections);
        } else {
            // The type is not recognized.  This shouldn't ever happen!
            G4cerr << "Invalid sensitive detector type: " << sensitiveDetectorTypeName << G4endl;
            G4Exception("", "", FatalException, "Unknown sensitive detector type.");
        }

        // Set the base attributes.
        sensitiveDetector->setEcut(SensitiveDetectorFactory::computeEcut(sensitiveDetectorType));
        sensitiveDetector->setVerbose(SensitiveDetectorFactory::convertVerbose(sensitiveDetectorType));
        sensitiveDetector->setEndcapFlag(StringUtil::toBool(sensitiveDetectorType->get_endcap_flag()));

        // Set the IdSpec.
        sensitiveDetector->setIdSpec(idspec);

        // Create DDSegmentation if exists, which requires idspec and SensitiveDetector to be instantiated beforehand.
        // FIXME: This is a weird place for this to happen I guess.
        if (dynamic_cast<CalorimeterSD*>(sensitiveDetector) != NULL)
            createDDSegmentation((CalorimeterSD*)sensitiveDetector, seq);

        // Add the list of HitProcessors.  This will automatically cause the HitProcessor setup code
        // to be called in order to configure it for this SD.
        sensitiveDetector->addHitProcessors(hitProcessors);

        // Register the SensitiveDetector with the LCDDProcessor.
        std::string sensitiveDetectorName = sensitiveDetector->GetName();
        LCDDProcessor::instance()->addSensitiveDetector(sensitiveDetectorName, sensitiveDetector);
    } else {
        // This should never really happen!
        G4Exception("", "", FatalException, "Failed cast to SensitiveDetectorType.");
    }

    return sensitiveDetector;
}

// FIXME: The grid size calculations should apply a length unit.
void SensitiveDetectorFactory::createDDSegmentation(CalorimeterSD* calorimeter, ContentSequence* seq) {

    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

    size_t count = seq->size();
    for (size_t i = 0; i < count; i++) {
        std::string childTag = seq->content(i).tag;
        const ContentGroup::ContentItem& segitem = seq->content(i);
        DD4hep::DDSegmentation::Segmentation* segmentation = NULL;
        if (childTag == "cartesian_grid_xy") {

            cartesian_grid_xy* element = dynamic_cast<cartesian_grid_xy*>(segitem.object);
            CartesianGridXY* cartesianGridXY = new CartesianGridXY(calorimeter->getIdSpec()->getFieldDescription());

            double gridSizeX, gridSizeY, offsetX, offsetY;
            gridSizeX = gridSizeY = offsetX = offsetY = 0;
            std::string rawValue = element->get_grid_size_x();
            gridSizeX = calc->Eval(rawValue);

            rawValue = element->get_grid_size_y();
            gridSizeY = calc->Eval(rawValue);

            rawValue = element->get_offset_x();
            offsetX = calc->Eval(rawValue);

            rawValue = element->get_offset_y();
            offsetY = calc->Eval(rawValue);

            cartesianGridXY->setGridSizeX(gridSizeX);
            cartesianGridXY->setGridSizeY(gridSizeY);
            cartesianGridXY->setOffsetX(offsetX);
            cartesianGridXY->setOffsetY(offsetY);

            segmentation = cartesianGridXY;

        } else if (childTag == "cartesian_grid_xyz") {
            cartesian_grid_xyz* element = dynamic_cast<cartesian_grid_xyz*>(segitem.object);
            CartesianGridXYZ* cartesianGridXYZ = new CartesianGridXYZ(calorimeter->getIdSpec()->getFieldDescription());

            double gridSizeX, gridSizeY, gridSizeZ, offsetX, offsetY, offsetZ;
            gridSizeX = gridSizeY = gridSizeZ = offsetX = offsetY = offsetZ = 0;

            std::string rawValue = element->get_grid_size_x();
            gridSizeX = calc->Eval(rawValue);

            rawValue = element->get_grid_size_y();
            gridSizeY = calc->Eval(rawValue);

            rawValue = element->get_grid_size_z();
            gridSizeZ = calc->Eval(rawValue);

            rawValue = element->get_offset_x();
            offsetX = calc->Eval(rawValue);

            rawValue = element->get_offset_y();
            offsetY = calc->Eval(rawValue);

            rawValue = element->get_offset_z();
            offsetZ = calc->Eval(rawValue);

            cartesianGridXYZ->setGridSizeX(gridSizeX);
            cartesianGridXYZ->setGridSizeY(gridSizeY);
            cartesianGridXYZ->setGridSizeZ(gridSizeZ);
            cartesianGridXYZ->setOffsetX(offsetX);
            cartesianGridXYZ->setOffsetY(offsetY);
            cartesianGridXYZ->setOffsetZ(offsetZ);

            segmentation = cartesianGridXYZ;
        } else if (childTag == "cartesian_grid_xz") {
            cartesian_grid_xz* element = dynamic_cast<cartesian_grid_xz*>(segitem.object);
            CartesianGridXZ* cartesianGridXZ = new CartesianGridXZ(calorimeter->getIdSpec()->getFieldDescription());

            double gridSizeX, gridSizeZ, offsetX, offsetZ;
            gridSizeX = gridSizeZ = offsetX = offsetZ = 0;

            std::string rawValue = element->get_grid_size_x();
            gridSizeX = calc->Eval(rawValue);

            rawValue = element->get_grid_size_z();
            gridSizeZ = calc->Eval(rawValue);

            rawValue = element->get_offset_x();
            offsetX = calc->Eval(rawValue);

            rawValue = element->get_offset_z();
            offsetZ = calc->Eval(rawValue);

            cartesianGridXZ->setGridSizeX(gridSizeX);
            cartesianGridXZ->setGridSizeZ(gridSizeZ);
            cartesianGridXZ->setOffsetX(offsetX);
            cartesianGridXZ->setOffsetZ(offsetZ);

            segmentation = cartesianGridXZ;
        } else if (childTag == "projective_cylinder") {

            projective_cylinder* element = dynamic_cast<projective_cylinder*>(segitem.object);
            ProjectiveCylinder* projectiveCylinder = new ProjectiveCylinder(calorimeter->getIdSpec()->getFieldDescription());

            double thetaBins, phiBins, offsetTheta, offsetPhi;
            thetaBins = phiBins = offsetTheta = offsetPhi;

            std::string rawValue = element->get_theta_bins();
            thetaBins = calc->Eval(rawValue);

            rawValue = element->get_phi_bins();
            phiBins = calc->Eval(rawValue);

            rawValue = element->get_offset_theta();
            offsetTheta = calc->Eval(rawValue);

            rawValue = element->get_offset_phi();
            offsetPhi = calc->Eval(rawValue);

            projectiveCylinder->setThetaBins(thetaBins);
            projectiveCylinder->setPhiBins(phiBins);
            projectiveCylinder->setOffsetTheta(offsetTheta);
            projectiveCylinder->setOffsetPhi(offsetPhi);

            segmentation = projectiveCylinder;
        }

        if (segmentation != NULL)
            calorimeter->setDDSegmentation(segmentation);
    }
}

SensitiveDetector* SensitiveDetectorFactory::createCalorimeter(const SAXObject* object, const std::vector<G4String>& hitsCollections) {
    const SensitiveDetectorType* sensitiveDetectorType = dynamic_cast<const SensitiveDetectorType*>(object);
    Segmentation* segmentation = 0;

    // Create the segmentation child object prior to the calorimeter.
    ContentSequence* seq = const_cast<ContentSequence*>(sensitiveDetectorType->get_content());
    size_t count = seq->size();
    for (size_t i = 0; i < count; i++) {
        std::string child_tag = seq->content(i).tag;
        const ContentGroup::ContentItem& segitem = seq->content(i);
        // Create segmentation using factory.
        if (isSegmentationTag(child_tag)) {
            segmentation = SegmentationFactory::createSegmentation(segitem.object, segitem.tag);
            break;
        }
    }

    // Create the CalorimeterSD object.
    CalorimeterSD* calorimeter = new CalorimeterSD(sensitiveDetectorType->get_name(), hitsCollections, segmentation);

    // Return the detector that was created.
    return calorimeter;
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
    // FIXME This should automatically know all segmentation types.
    //       Can they be read from the schema?
    //       http://xerces-c.sourcearchive.com/documentation/3.1.1-1/SchemaGrammar_8hpp_source.html
    return (s == "projective_cylinder_old" ||
            s == "grid_xyz" ||
            s == "global_grid_xy" ||
            s == "projective_zplane" ||
            s == "cell_readout_2d");
}
