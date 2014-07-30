#ifndef LCDD_DETECTORS_SENSITIVEDETECTORFACTORY_HH_
#define LCDD_DETECTORS_SENSITIVEDETECTORFACTORY_HH_ 1

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/schema/SensitiveDetectorType.hh"
#include "lcdd/schema/calorimeter.hh"
#include "lcdd/schema/tracker.hh"
#include "lcdd/schema/IdSpecType.hh"
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/segmentation/SegmentationFactory.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/id/IdSpec.hh"

// GDML
#include "G4Processor/GDMLProcessor.h"

#include "Saxana/SAXObject.h"

class TrackerSD;
class ScorerSD;
class CalorimeterSD;

/**
 * @brief Creates SensitiveDetector objects from detector tag names and parameters.
 */
class SensitiveDetectorFactory {

private:

    /**
     * Class constructor which is private.
     */
    SensitiveDetectorFactory() {
    }

    /**
     * Class destructor.
     */
    virtual ~SensitiveDetectorFactory() {
    }

public:

    /**
     * Create a SensitiveDetector object.
     * @param[in] object The SAXObject of the detector.
     */
    static SensitiveDetector* createSensitiveDetector(const SAXObject* object);

private:

    /**
     * Create a calorimeter SD from XML.
     * @param[in] The SensitiveDetectorType object.
     * @param[in] The object pointing to the calorimeter element.
     * @param[in] The list of hits collection names.
     * @return The CalorimeterSD as a generic SensitiveDetector.
     */
    static SensitiveDetector* createCalorimeter(const SAXObject* object, const std::vector<G4String>& hitsCollections);

    /**
     * Create a TrackerSD object.
     * @param[in] object The SAXObject of the detector.
     */
    static TrackerSD* createTracker(const SAXObject* object, const std::vector<G4String>& hitsCollections);

    /**
     * Compute the ecut for a detector.
     * @param[in] sdt The SAXObject of the SD.
     * @return The ecut (GeV).
     */
    static double computeEcut(const SensitiveDetectorType* sdt);

    /**
     * Convert input parameters to a verbosity level.
     * @param[in] sdt The SAXObject of the SD.
     * @return The verbosity level.
     */
    static int convertVerbose(const SensitiveDetectorType* sdt);

    /**
     * Check if the string is a legitimate Segmentation tag.
     * @param[in] s The name of the tag.
     * @return True if segmentation tag is valid; false if not.
     */
    static bool isSegmentationTag(const std::string& s);
};

#endif
