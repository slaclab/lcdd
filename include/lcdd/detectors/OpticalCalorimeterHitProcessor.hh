// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/OpticalCalorimeterHitProcessor.hh,v 1.3 2013-11-14 00:46:45 jeremy Exp $

#ifndef LCDD_DETECTORS_OPTICALCALORIMETERHITPROCESSOR_HH_
#define LCDD_DETECTORS_OPTICALCALORIMETERHITPROCESSOR_HH_ 1

// LCDD
#include "lcdd/detectors/LegacyCalorimeterHitProcessor.hh"
#include "lcdd/detectors/Cerenkov.hh"
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief HitProcessor to create CalorimeterHit objects in an optical calorimeter.
 */
class OpticalCalorimeterHitProcessor: public LegacyCalorimeterHitProcessor {
public:

    /**
     * An enum for the two hit collections (cerenkov and edep).
     */
    enum HCType {
        eEdep = 0, eCerenkov = 1
    };

public:

    /**
     * Class constructor.
     * @param[in] calorimeter The calorimeter SD.
     */
    OpticalCalorimeterHitProcessor(CalorimeterSD* calorimeter);

    /**
     * Class destructor.
     */
    virtual ~OpticalCalorimeterHitProcessor();

    /**
     * Process steps to produce hits.
     * @param[in] step The G4Step object.
     */
    bool processHits(G4Step* step);

private:

    /**
     * Get the global hit position from a pre step point.
     * @param[in] aPreStepPoint The pre step point.
     */
    G4ThreeVector getGlobalHitPosition(const G4StepPoint* aPreStepPoint);

private:

    Cerenkov* _cerenGenerator;
};

/**
 * The factory for creating new OpticalCalorimeterHitProcessor objects.
 */
class OpticalCalorimeterHitProcessorFactory: public HitProcessorFactory {

public:

    HitProcessor* createHitProcessor(SensitiveDetector* sd) {
        return new OpticalCalorimeterHitProcessor(dynamic_cast<CalorimeterSD*>(sd));
    }

    const std::string& handlesType() {
        static std::string typeName = "OpticalCalorimeterHitProcessor";
        return typeName;
    }
};

#endif
