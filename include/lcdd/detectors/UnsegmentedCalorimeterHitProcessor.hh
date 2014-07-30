#ifndef LCDD_DETECTORS_UNSEGMENTEDCALORIMETERHITPROCESSOR_HH_
#define LCDD_DETECTORS_UNSEGMENTEDCALORIMETERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/CalorimeterHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @class UnsegmentedCalorimeterHitProcessor
 * HitProcessor that produces CalorimeterHit objects with no virtual geometry segmentation.
 */
class UnsegmentedCalorimeterHitProcessor: public CalorimeterHitProcessor {

public:

    /**
     * Class constructor.
     * @param[in] calorimeter The calorimeter SD.
     */
    UnsegmentedCalorimeterHitProcessor(CalorimeterSD* calorimeter);

    /**
     * Class destructor.
     */
    virtual ~UnsegmentedCalorimeterHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step The G4Step object.
     */
    bool processHits(G4Step* step);
};

/**
 * The factory for creating new UnsegmentedCalorimeterHitProcessor objects.
 */
class UnsegmentedCalorimeterHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new UnsegmentedCalorimeterHitProcessor(dynamic_cast<CalorimeterSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "UnsegmentedCalorimeterHitProcessor";
        return typeName;
    }
};

#endif
