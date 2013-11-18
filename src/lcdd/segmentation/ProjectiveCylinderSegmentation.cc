// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/segmentation/ProjectiveCylinderSegmentation.cc,v 1.2 2013-11-13 23:02:58 jeremy Exp $

// LCDD
#include "lcdd/segmentation/ProjectiveCylinderSegmentation.hh"
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4StepPoint.hh"
#include "G4NavigationHistory.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Tubs.hh"

ProjectiveCylinderSegmentation::ProjectiveCylinderSegmentation(G4int ntheta, G4int nphi) :
        ProjectiveSegmentation(ntheta, nphi) {
}

ProjectiveCylinderSegmentation::~ProjectiveCylinderSegmentation() {
}

double ProjectiveCylinderSegmentation::getRadius(const G4Step* aStep) {
    return ReadoutUtil::computeTubsMidRadius(ReadoutUtil::getTubs(aStep));
}

/*
 double ProjectiveCylinderSegmentation::getRadius(const G4StepPoint* aPreStepPoint)
 {
 return ReadoutUtil::computeTubsMidRadius(ReadoutUtil::getTubs(aPreStepPoint));
 }
 */

double ProjectiveCylinderSegmentation::getZ(const G4Step* aStep) {
    double rcyl = getRadius(aStep);

    double ctheta = getThetaDim(aStep);

    // ctheta in 0 to pi ...
    // ctheta < pi/2 should be negative

    double zcell = rcyl / tan(ctheta);

    return zcell;
}
/*
 double ProjectiveCylinderSegmentation::getZ(const G4StepPoint* aPreStepPoint)
 {
 double rcyl = getRadius(aPreStepPoint);

 double ctheta = getThetaDim(aPreStepPoint);

 // ctheta in 0 to pi ...
 // ctheta < pi/2 should be negative

 double zcell = rcyl / tan(ctheta);

 return zcell;
 }
 */
bool ProjectiveCylinderSegmentation::isValidSolid(G4VSolid* s) {
    bool valid = Segmentation::isValidSolid(s);

    if (valid) {
        if (s->GetEntityType() != "G4Tubs") {
            valid = false;
        }
    }

    return valid;
}
