#ifndef LCDD_DETECTORS_CALORIMETERHITPROCESSOR_HH_
#define LCDD_DETECTORS_CALORIMETERHITPROCESSOR_HH_ 1

// Geant4
#include "G4Step.hh"

// LCDD
#include "lcdd/detectors/HitProcessor.hh"
#include "lcdd/detectors/CalorimeterSD.hh"

/**
 * @brief Interface for processing step data to produce CalorimeterHits.
 */
class CalorimeterHitProcessor: public HitProcessor {

public:

    /**
     * Class destructor.
     */
    virtual ~CalorimeterHitProcessor();

protected:

    /**
     * Class constructor.
     * @param[in] ro The CellReadout used by the processor.
     */
    CalorimeterHitProcessor(CalorimeterSD* calorimeter);

public:

    /**
     * Process steps to make hits.
     * @param[in] step The G4Step object of the energy deposition.
     * @todo This should really be pure virtual, but I can't get it to link correctly.
     */
    virtual bool processHits(G4Step* step);

protected:
    CalorimeterSD* _calorimeter;
};

#endif
