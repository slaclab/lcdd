#include "lcdd/detectors/StepReadout.hh"

// LCDD
#include "lcdd/detectors/ReadoutUtil.hh"

// G4
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4VSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4TouchableHandle.hh"
#include "G4Region.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

StepReadout::StepReadout() :
        _step(0) {
}

StepReadout::~StepReadout() {
}

void StepReadout::setStep(G4Step* s) {
    _step = s;
}

G4Step* StepReadout::step() const {
    return _step;
}

bool StepReadout::hasStep() const {
    return (0 != _step);
}

G4StepPoint* StepReadout::pre() const {
    return step()->GetPreStepPoint();
}

G4StepPoint* StepReadout::post() const {
    return step()->GetPostStepPoint();
}

G4VPhysicalVolume* StepReadout::prePV() const {
    return preTouchableHandle()->GetVolume();
}

G4VPhysicalVolume* StepReadout::postPV() const {
    return postTouchableHandle()->GetVolume();
}

G4VSolid* StepReadout::preSolid() const {
    return preLV()->GetSolid();
}

G4VSolid* StepReadout::postSolid() const {
    return postLV()->GetSolid();
}

G4LogicalVolume* StepReadout::preLV() const {
    return prePV()->GetLogicalVolume();
}

G4LogicalVolume* StepReadout::postLV() const {
    return postPV()->GetLogicalVolume();
}

G4Material* StepReadout::preMaterial() const {
    return pre()->GetMaterial();
}

G4Material* StepReadout::postMaterial() const {
    return post()->GetMaterial();
}

G4VSensitiveDetector* StepReadout::preSD() const {
    return getSD(pre());
}

G4VSensitiveDetector* StepReadout::postSD() const {
    return getSD(post());
}

G4VSensitiveDetector* StepReadout::getSD(G4StepPoint* stepPoint) const {
    return stepPoint->GetPhysicalVolume()->GetLogicalVolume()->GetSensitiveDetector();
}

bool StepReadout::hasSameSD() const {
    bool r = false;

    // post vol has an SD
    if (0 != postSD()) {

        // post SD same as pre SD
        if (preSD() == postSD()) {
            r = true;
        }
    }

    return r;
}

G4ThreeVector StepReadout::volumePosition(G4TouchableHandle theTouchable) const {
    return theTouchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(_origin);
}

G4ThreeVector StepReadout::preVolumePosition() const {
    return volumePosition(preTouchableHandle());
}

G4ThreeVector StepReadout::postVolumePosition() const {
    return volumePosition(postTouchableHandle());
}

double StepReadout::edep() const {
    return step()->GetTotalEnergyDeposit();
}

G4Track* StepReadout::track() const {
    return step()->GetTrack();
}

double StepReadout::globalTime() const {
    return track()->GetGlobalTime();
}

int StepReadout::trackID() const {
    return track()->GetTrackID();
}

G4ThreeVector StepReadout::momentum() const {
    return track()->GetMomentum();
}

G4ThreeVector StepReadout::prePosition() const {
    return pre()->GetPosition();
}

G4ThreeVector StepReadout::midPosition() const {
    return ReadoutUtil::computeThreeVectorMean(prePosition(), postPosition());
}

G4ThreeVector StepReadout::postPosition() const {
    return post()->GetPosition();
}

G4ThreeVector StepReadout::preMomentum() const {
    return pre()->GetMomentum();
}

G4ThreeVector StepReadout::postMomentum() const {
    return post()->GetMomentum();
}

G4ThreeVector StepReadout::meanMomentum() const {
    return ReadoutUtil::computeThreeVectorMean(preMomentum(), postMomentum());
}

G4TouchableHandle StepReadout::preTouchableHandle() const {
    return pre()->GetTouchableHandle();
}

G4TouchableHandle StepReadout::postTouchableHandle() const {
    return post()->GetTouchableHandle();
}

bool StepReadout::isGeantino() {
    return ReadoutUtil::isGeantino(step());
}
