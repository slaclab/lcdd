// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/LegacyCalorimeterHitProcessor.hh,v 1.4 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_LEGACYCALORIMETERHITPROCESSOR_HH
#define LCDD_DETECTORS_LEGACYCALORIMETERHITPROCESSOR_HH 1

// LCDD
#include "lcdd/detectors/CalorimeterHitProcessor.hh"
#include "lcdd/detectors/CalorimeterSD.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief Implementation of hit processing behavior for CalorimeterSD objects with Segmentation.
 * @todo Change name to SegmentedCalorimeterHitProcessor.
 */
class LegacyCalorimeterHitProcessor: public CalorimeterHitProcessor {

public:

    /**
     * Class constructor.
     */
    LegacyCalorimeterHitProcessor(CalorimeterSD* calorimeter);

    /**
     * Class destructor.
     */
    virtual ~LegacyCalorimeterHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     */
    bool processHits(G4Step* step);
};

/**
 * The factory for creating new LegacyCalorimeterHitProcessor objects.
 */
class LegacyCalorimeterHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new LegacyCalorimeterHitProcessor(dynamic_cast<CalorimeterSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "LegacyCalorimeterHitProcessor";
        return typeName;
    }
};

#endif
