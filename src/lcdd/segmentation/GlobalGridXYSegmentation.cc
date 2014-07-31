#include "lcdd/segmentation/GlobalGridXYSegmentation.hh"

// LCDD
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4NavigationHistory.hh"

GlobalGridXYSegmentation::GlobalGridXYSegmentation(double gridSizeX, double gridSizeY) :
        Segmentation(Segmentation::eNonprojective), _gridSizeX(gridSizeX), _gridSizeY(gridSizeY) {
    setBinNames();
}

GlobalGridXYSegmentation::~GlobalGridXYSegmentation() {
}

void GlobalGridXYSegmentation::setBinNames() {
    addBinName("x");
    addBinName("y");
    addBinName("z");
}

G4ThreeVector GlobalGridXYSegmentation::getGlobalHitPosition(const G4Step* aStep) {
    // Compute the midpoint of the global step.
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);

    // Create 3vec for cell position.
    G4ThreeVector globalCellPos;

    // Set binned coordinates of cell position.
    globalCellPos.setX(computeDimX(computeBinX(globalStepPos)));
    globalCellPos.setY(computeDimY(computeBinY(globalStepPos)));

    // Set Z coordinate of cell position from the volume's Z center position.
    G4ThreeVector vpos = ReadoutUtil::getVolumeGlobalPosition(aStep->GetPreStepPoint());
    globalCellPos.setZ(vpos.z());

    return globalCellPos;
}

void GlobalGridXYSegmentation::setBins(const G4Step* aStep) {
    // Compute the midpoint of the step.
    G4ThreeVector globalStepPos = ReadoutUtil::computeMidPos(aStep);

    // Compute the bin values.
    int binX = computeBinX(globalStepPos);
    int binY = computeBinY(globalStepPos);

    // Set the bin values.
    setBin(0, binX);
    setBin(1, binY);
}

int GlobalGridXYSegmentation::computeBinX(const G4ThreeVector& stepPos) {
    return Segmentation::computeBin(stepPos.x(), _gridSizeX);
}

int GlobalGridXYSegmentation::computeBinY(const G4ThreeVector& stepPos) {
    return Segmentation::computeBin(stepPos.y(), _gridSizeY);
}

double GlobalGridXYSegmentation::computeDimX(int bin) {
    return Segmentation::computeDim(bin, _gridSizeX);
}

double GlobalGridXYSegmentation::computeDimY(int bin) {
    return Segmentation::computeDim(bin, _gridSizeY);
}
