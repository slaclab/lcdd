// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/HitProcessorManager.cc,v 1.3 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/HitProcessorManager.hh"
#include "lcdd/detectors/LegacyCalorimeterHitProcessor.hh"
#include "lcdd/detectors/UnsegmentedCalorimeterHitProcessor.hh"
#include "lcdd/detectors/OpticalCalorimeterHitProcessor.hh"
#include "lcdd/detectors/BasicTrackerHitProcessor.hh"
#include "lcdd/detectors/ScoringTrackerHitProcessor.hh"
#include "lcdd/detectors/StepCombiningTrackerHitProcessor.hh"

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
    registerFactory(new LegacyCalorimeterHitProcessorFactory());
    registerFactory(new UnsegmentedCalorimeterHitProcessorFactory());
    registerFactory(new OpticalCalorimeterHitProcessorFactory());
    registerFactory(new ScoringTrackerHitProcessorFactory());
    registerFactory(new BasicTrackerHitProcessorFactory());
    registerFactory(new StepCombiningTrackerHitProcessorFactory());
}

void HitProcessorManager::registerFactory(HitProcessorFactory* factory) {
    _factories[factory->handlesType()] = factory;
}

HitProcessorFactory* HitProcessorManager::getFactory(const std::string& hitProcessorType) {
    return _factories[hitProcessorType];
}
