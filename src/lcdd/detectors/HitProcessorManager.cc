#include "lcdd/detectors/HitProcessorManager.hh"

// LCDD
#include "lcdd/detectors/BasicCalorimeterHitProcessor.hh"
#include "lcdd/detectors/BasicTrackerHitProcessor.hh"
#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"
#include "lcdd/detectors/DDSegmentationCalorimeterHitProcessor.hh"

HitProcessorManager* HitProcessorManager::_manager = 0;

HitProcessorManager::HitProcessorManager() {
    registerDefaultFactories();
}

HitProcessorManager::~HitProcessorManager() {
}

HitProcessorManager* HitProcessorManager::instance() {
    if (_manager == 0) {
        _manager = new HitProcessorManager();
    }
    return _manager;
}

void HitProcessorManager::registerDefaultFactories() {
    registerFactory(new BasicCalorimeterHitProcessorFactory());
    registerFactory(new ScoringTrackerHitProcessorFactory());
    registerFactory(new BasicTrackerHitProcessorFactory());
    registerFactory(new DDSegmentationCalorimeterHitProcessorFactory());
}

void HitProcessorManager::registerFactory(HitProcessorFactory* factory) {
    _factories[factory->handlesType()] = factory;
}

HitProcessorFactory* HitProcessorManager::getFactory(const std::string& hitProcessorType) {
    return _factories[hitProcessorType];
}
