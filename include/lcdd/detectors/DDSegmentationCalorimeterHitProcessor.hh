/*
 * DDSegmentationCalorimeterHitProcessor.hh
 *
 *  Created on: Aug 8, 2014
 *      Author: jeremym
 */
#ifndef LCDD_DETECTORS_DDSEGMENTATIONCALORIMETERHITPROCESSOR_HH_
#define LCDD_DETECTORS_DDSEGMENTATIONCALORIMETERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/CalorimeterHitProcessor.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief
 * Implementation of hit processing behavior using the DDSegmentation API for the Segmentation.
 */
class DDSegmentationCalorimeterHitProcessor: public CalorimeterHitProcessor {

public:

    /**
     * Class constructor.
     */
    DDSegmentationCalorimeterHitProcessor();

    /**
     * Class destructor.
     */
    virtual ~DDSegmentationCalorimeterHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     */
    bool processHits(G4Step* step);
};

/**
 * @brief
 * The factory for creating new DDSegmentationCalorimeterHitProcessor objects
 */
class DDSegmentationCalorimeterHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor() {
        return new DDSegmentationCalorimeterHitProcessor();
    }

    const std::string& handlesType() {
        static std::string typeName = "DDSegmentationCalorimeterHitProcessor";
        return typeName;
    }
};

#endif /* LCDD_DETECTORS_DDSEGMENTATIONCALORIMETERHITPROCESSOR_HH_ */
