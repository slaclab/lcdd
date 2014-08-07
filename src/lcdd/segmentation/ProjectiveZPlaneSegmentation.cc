#include "lcdd/segmentation/ProjectiveZPlaneSegmentation.hh"

// LCDD
#include "lcdd/detectors/ReadoutUtil.hh"

ProjectiveZPlaneSegmentation::ProjectiveZPlaneSegmentation(G4int ntheta, G4int nphi) :
        ProjectiveSegmentation(ntheta, nphi) {
}

ProjectiveZPlaneSegmentation::~ProjectiveZPlaneSegmentation() {
}

double ProjectiveZPlaneSegmentation::getRadius(const G4Step* aStep) {
    double zcell = getZ(aStep);
    double ctheta = ProjectiveSegmentation::getThetaDim(aStep);
    double rcyl = zcell * tan(ctheta);
    return rcyl;
}

double ProjectiveZPlaneSegmentation::getZ(const G4Step* aStep) {
    G4ThreeVector gpos = ReadoutUtil::getVolumeGlobalPosition(aStep->GetPreStepPoint(), G4ThreeVector());
    return gpos.z();
}
