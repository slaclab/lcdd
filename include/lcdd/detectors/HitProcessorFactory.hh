#ifndef LCDD_DETECTORS_HITPROCESSORFACTORY_HH_
#define LCDD_DETECTORS_HITPROCESSORFACTORY_HH_

// LCDD
#include "lcdd/detectors/HitProcessor.hh"
#include "lcdd/detectors/SensitiveDetector.hh"

class HitProcessorFactory {
public:

    /**
     * Class constructor.
     */
    HitProcessorFactory();

    /**
     * Class destructor.
     */
    virtual ~HitProcessorFactory();

public:

    /**
     * Create a HitProcessor for the given SensitiveDetector.
     * @param[in] sd The SensitiveDetector to which the HitProcessor will be added.
     * @return The specific implementation of HitProcessor produced by this factory.
     */
    virtual HitProcessor* createHitProcessor(SensitiveDetector* sd) = 0;

    /**
     * Get the type of HitProcessor created by this factory e.g. name of the class.
     * @return The name of the HitProcessor class produced by this factory.
     */
    virtual const std::string& handlesType() = 0;
};

#endif
