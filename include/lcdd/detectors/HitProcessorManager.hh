// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/HitProcessorManager.hh,v 1.3 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_HITPROCESSORMANAGER_HH
#define LCDD_DETECTORS_HITPROCESSORMANAGER_HH 1

// LCDD
#include "lcdd/detectors/HitProcessorFactory.hh"

class HitProcessorManager {

private:

    typedef std::map<std::string, HitProcessorFactory*> HitProcessorFactories;

public:

    /**
     * Class destructor.
     */
    virtual ~HitProcessorManager();

    /**
     * Get a factory for creating a HitProcessor of a specific concrete type.
     * @param[in] hitProcessorType The name of the HitProcessor type.
     * @return The HitProcessorFactory for creating HitProcessors with the given type.
     */
    HitProcessorFactory* getFactory(const std::string& hitProcessorType);

    /**
     * Register a factory for creating HitProcessor objects with a certain type.
     * @param[in] factory A pointer to the HitProcessorFactory which should be registered.
     * @note The method HitProcessorFactory::handlesType will be used to get the name of the type.
     */
    void registerFactory(HitProcessorFactory* factory);

    /**
     * Get the singleton instance of this class.
     * @return The singleton instance.
     */
    static HitProcessorManager* instance();

private:

    /**
     * Class constructor.
     */
    HitProcessorManager();

    /**
     * Create and register the default set of factories for creating new HitProcessor objects.
     */
    void registerDefaultFactories();

private:

    HitProcessorFactories _factories;
    static HitProcessorManager* _manager;
};

#endif
