// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/Segmentation.cc,v 1.2 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/segmentation/Segmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

Segmentation::Segmentation(EType segType, int nbins) :
        _numBins(nbins), _type(segType) {
    // Fill bins with zeros.
    for (int i=0; i<_numBins; i++) {
        _bins.push_back(0);
    }
}

Segmentation::~Segmentation() {
}

void Segmentation::setBin(int binIdx, int binVal) {
    _bins[binIdx] = binVal;
}

int Segmentation::getNumberOfBins() {
    return _numBins;
}

const std::vector<int>& Segmentation::getBins() {
    return _bins;
}

Segmentation::EType Segmentation::getType() {
    return _type;
}

G4ThreeVector Segmentation::getLocalHitPosition(const G4ThreeVector& localStepPos) {
    return localStepPos;
}

void Segmentation::printOutBins(std::ostream& os, const std::vector<int>& bins) {
    os << "segmentationBins <" << bins.size() << "> :: ";
    for (std::vector<int>::const_iterator iter = bins.begin(); iter != bins.end(); iter++) {
        os << *iter << " ";
    }
    os << std::endl;
}

bool Segmentation::isValidSolid(G4VSolid* s) {
    bool valid = true;
    if (0 == s) {
        valid = false;
    }
    return valid;
}

const G4String& Segmentation::getTypeString() {
    static G4String typestr;
    if (_type == Segmentation::eProjective) {
        typestr = "Projective";
    } else if (_type == Segmentation::eNonprojective) {
        typestr = "Nonprojective";
    } else {
        typestr = "Unknown";
    }
    return typestr;
}

int Segmentation::getBin(int idx) {
    return _bins.at(idx);
}

const std::string& Segmentation::getBinName(int idx) {
    return _binNames.at(idx);
}

void Segmentation::addBinName(const std::string& binName) {
    _binNames.push_back(binName);
}

const std::vector<std::string>& Segmentation::getBinNames() {
    return _binNames;
}

void Segmentation::printOutBins(std::ostream& os) {
    printOutBins(os, _bins);
}

int Segmentation::computeBin(double localDim, double gridDim) {
    return int(floor(localDim / gridDim));
}

double Segmentation::computeDim(const int &bin, const double &incr) {
    return (double(bin) + .5) * incr;
}
