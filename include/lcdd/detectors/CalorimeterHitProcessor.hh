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
    virtual ~CalorimeterHitProcessor() {
    }

protected:

    /**
     * Class constructor.
     * @param[in] ro The CellReadout used by the processor.
     */
    CalorimeterHitProcessor()
        : _calorimeter(NULL) {
    }

public:

    /**
     * Process steps to make hits.
     * @param[in] step The G4Step object of the energy deposition.
     * @todo This should really be pure virtual, but I can't get it to link correctly.
     */
    virtual bool processHits(G4Step* step) = 0;

    /**
     * Get the Calorimeter associated with this HitProcessor.
     */
    CalorimeterSD* getCalorimeter() {
        return dynamic_cast<CalorimeterSD*>(getSensitiveDetector());
    }

    /**
     * Override super class method to set reference to CalorimeterSD.
     * @param[in] detector The SensitiveDetector associated to this HitProcessor.
     */
    void setSensitiveDetector(SensitiveDetector* detector) {
        HitProcessor::setSensitiveDetector(detector);
        _calorimeter = dynamic_cast<CalorimeterSD*>(getSensitiveDetector());
    }

protected:

    CalorimeterSD* _calorimeter;

};

#endif
