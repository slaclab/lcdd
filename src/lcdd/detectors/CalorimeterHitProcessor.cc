// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/CalorimeterHitProcessor.cc,v 1.6 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/CalorimeterHitProcessor.hh"
#include "lcdd/detectors/CalorimeterSD.hh"

CalorimeterHitProcessor::CalorimeterHitProcessor(CalorimeterSD* calorimeter) :
        _calorimeter(calorimeter) {
}

CalorimeterHitProcessor::~CalorimeterHitProcessor() {
}

bool CalorimeterHitProcessor::processHits(G4Step* step) {
    return false;
}
