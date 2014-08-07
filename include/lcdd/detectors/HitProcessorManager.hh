#ifndef LCDD_DETECTORS_HITPROCESSORMANAGER_HH_
#define LCDD_DETECTORS_HITPROCESSORMANAGER_HH_ 1

// LCDD
#include "lcdd/detectors/HitProcessorFactory.hh"

/**
 * @brief
 * The global registry of all HitProcessor objects
 */
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
