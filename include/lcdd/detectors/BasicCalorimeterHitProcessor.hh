#ifndef LCDD_DETECTORS_LEGACYCALORIMETERHITPROCESSOR_HH_
#define LCDD_DETECTORS_LEGACYCALORIMETERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/CalorimeterHitProcessor.hh"
#include "lcdd/detectors/CalorimeterSD.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief
 * Implementation of hit processing behavior for CalorimeterSD objects with Segmentation.
 */
class BasicCalorimeterHitProcessor: public CalorimeterHitProcessor {

public:

    /**
     * Class constructor.
     */
    BasicCalorimeterHitProcessor();

    /**
     * Class destructor.
     */
    virtual ~BasicCalorimeterHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     */
    bool processHits(G4Step* step);
};

/**
 * @brief
 * The factory for creating new BasicCalorimeterHitProcessor objects
 */
class BasicCalorimeterHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor() {
        return new BasicCalorimeterHitProcessor();
    }

    const std::string& handlesType() {
        static std::string typeName = "BasicCalorimeterHitProcessor";
        return typeName;
    }
};

#endif
