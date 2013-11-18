// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/detectors/ReadoutUtil.cc,v 1.3 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/detectors/ReadoutUtil.hh"

// Geant4
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"

// STL
#include <cmath>

const double ReadoutUtil::PI = acos(-1);

G4ThreeVector ReadoutUtil::computeThreeVectorMean(const G4ThreeVector& vec1, const G4ThreeVector& vec2) {
    return (0.5 * (vec1 + vec2));
}

G4double ReadoutUtil::computeDistance(const G4ThreeVector& vec1, const G4ThreeVector& vec2) {
    return (sqrt(pow(vec1.x() - vec2.x(), 2) + pow(vec1.y() - vec2.y(), 2) + pow(vec1.z() - vec2.z(), 2)));
}

G4double ReadoutUtil::computeDistance(const G4Step* aStep) {
    return computeDistance(aStep->GetPreStepPoint()->GetPosition(), aStep->GetPostStepPoint()->GetPosition());
}

G4ThreeVector ReadoutUtil::computeMidPos(const G4Step* aStep) {
    return computeThreeVectorMean(aStep->GetPreStepPoint()->GetPosition(), aStep->GetPostStepPoint()->GetPosition());
}

G4VSolid* ReadoutUtil::getSolidFromStepPoint(const G4StepPoint* aStepPoint) {
    assert(aStepPoint);

    return aStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetSolid();
}

//G4TouchableHandle ReadoutUtil::getTouchableFromStep(const G4Step* aStep)
//{
//    return aStep->GetPreStepPoint()->GetTouchableHandle();
//}

G4ThreeVector ReadoutUtil::getVolumeGlobalPosition(const G4StepPoint* aStepPoint, const G4ThreeVector& pnt) {
    return aStepPoint->GetTouchableHandle()->GetHistory()->GetTopTransform().Inverse().TransformPoint(pnt);
}

G4ThreeVector ReadoutUtil::getVolumeGlobalPosition(const G4StepPoint* aStepPoint) {
    return getVolumeGlobalPosition(aStepPoint, G4ThreeVector());
}

const G4Tubs* ReadoutUtil::getTubs(const G4Step* aStep) {
    const G4Tubs* tubs = 0;
    G4VSolid* solid = ReadoutUtil::getSolidFromStepPoint(aStep->GetPreStepPoint());
    tubs = static_cast<const G4Tubs*>(solid);
    return tubs;
}
const G4Tubs* ReadoutUtil::getTubs(const G4StepPoint* aPreStepPoint) {
    const G4Tubs* tubs = 0;
    G4VSolid* solid = ReadoutUtil::getSolidFromStepPoint(aPreStepPoint);
    tubs = static_cast<const G4Tubs*>(solid);
    return tubs;
}
double ReadoutUtil::computeTubsMidRadius(const G4Tubs* tubs) {
    double thickness = getTubsThickness(tubs);
    double rcyl = tubs->GetInnerRadius() + thickness / 2;
    return rcyl;
}

double ReadoutUtil::computeTubsMidRadius(const G4Step* aStep) {
    return computeTubsMidRadius(ReadoutUtil::getTubs(aStep));
}
double ReadoutUtil::computeTubsMidRadius(const G4StepPoint* aPreStepPoint) {
    return computeTubsMidRadius(ReadoutUtil::getTubs(aPreStepPoint));
}

double ReadoutUtil::getTubsThickness(const G4Tubs* tubs) {
    return tubs->GetOuterRadius() - tubs->GetInnerRadius();
}

G4ThreeVector ReadoutUtil::transformLocalToGlobal(const G4Step* aStep, const G4ThreeVector& localPos) {
    // get touchable from PreStepPoint
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();

    // compute global pos using local point and touchable
    G4ThreeVector globalPos = theTouchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(localPos);

    return globalPos;
}
G4ThreeVector ReadoutUtil::transformLocalToGlobal(const G4StepPoint* aPreStepPoint, const G4ThreeVector& localPos) {
    // get touchable from PreStepPoint
    G4TouchableHandle theTouchable = aPreStepPoint->GetTouchableHandle();

    // compute global pos using local point and touchable
    G4ThreeVector globalPos = theTouchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(localPos);

    return globalPos;
}
G4ThreeVector ReadoutUtil::transformGlobalToLocal(const G4Step* aStep, const G4ThreeVector& globalPos) {
    // get touchable from PreStepPoint
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();

    // compute local pos using global point and touchable
    G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(globalPos);

    return localPos;
}
G4ThreeVector ReadoutUtil::transformGlobalToLocal(const G4StepPoint* aPreStepPoint, const G4ThreeVector& globalPos) {
    // get touchable from PreStepPoint
    G4TouchableHandle theTouchable = aPreStepPoint->GetTouchableHandle();

    // compute local pos using global point and touchable
    G4ThreeVector localPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(globalPos);

    return localPos;
}

std::vector<G4VPhysicalVolume*> ReadoutUtil::getPhysVolList(G4Step* aStep) {
    std::vector<G4VPhysicalVolume*> physVols;

    // get touchable from PreStepPoint
    G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();

    G4int hdepth = theTouchable->GetHistoryDepth();

    const G4NavigationHistory* theTouchableHistory = theTouchable->GetHistory();

    for (int i = hdepth; i > 0; i--) {
        G4VPhysicalVolume* pv = theTouchableHistory->GetVolume(i);
        physVols.push_back(pv);

#ifdef ID_DEBUG
        G4cout << "pushed back <" << pv->GetName() << ">" << G4endl;
#endif
    }

    return physVols;
}

int ReadoutUtil::getVolumeNumber(G4TouchableHandle theTouchable, int historyDepth) {
    bool no_depth = false;

    if (historyDepth == -1) {
        no_depth = true;
    }

    G4VPhysicalVolume *pv = 0;

    // pv only with depth arg
    if (!no_depth) {
        pv = theTouchable->GetHistory()->GetVolume(historyDepth);
    }

    int vnum = -1;

    // rep num: no pv, replicated, parameterised
    if (!pv || pv->IsReplicated() || pv->IsParameterised()) {

        // no depth
        if (no_depth) {
            vnum = theTouchable->GetReplicaNumber();
        }
        // use history depth
        else {
            vnum = theTouchable->GetReplicaNumber(historyDepth);
        }
    } else {
        // copy num: placement
        vnum = pv->GetCopyNo();
    }

    return vnum;
}

bool ReadoutUtil::isGeantino(G4Step* aStep) {
    G4ParticleDefinition* def = aStep->GetTrack()->GetDefinition();
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition())
        return true;
    else
        return false;
}
