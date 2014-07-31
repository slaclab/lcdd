#include "lcdd/detectors/CalorimeterHitProcessor.hh"

// LCDD
#include "lcdd/detectors/CalorimeterSD.hh"

CalorimeterHitProcessor::CalorimeterHitProcessor(CalorimeterSD* calorimeter) :
        _calorimeter(calorimeter) {
}

CalorimeterHitProcessor::~CalorimeterHitProcessor() {
}

bool CalorimeterHitProcessor::processHits(G4Step* step) {
    return false;
}
