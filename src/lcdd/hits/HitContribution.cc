// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/hits/HitContribution.cc,v 1.4 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/hits/HitContribution.hh"
#include "lcdd/hits/TrackInformation.hh"

// Geant4
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

HitContribution::HitContribution() :
        _trackID(-1), _edep(0), _PdgId(9999999), _globalTime(0) {
    ;
}

HitContribution::HitContribution(G4int trackID, G4double edep, G4int PDGID, G4double globalTime) :
        _trackID(trackID), _edep(edep), _PdgId(PDGID), _globalTime(globalTime) {
    ;
}

HitContribution::~HitContribution() {
    ;
}

HitContribution::HitContribution(const G4Step* aStep) {
    // Get the track.
    const G4Track* aTrack = aStep->GetTrack();

    // Get the track information.
    TrackInformation* trkInfo = static_cast<TrackInformation*>(aTrack->GetUserInformation());

    // Get the track ID.
    _trackID = trkInfo->getOriginalTrackID();

    // Set edep according to type of track.
    //if (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    //    _edep = aTrack->GetTotalEnergy();
    //} else {
    _edep = aStep->GetTotalEnergyDeposit();
    //}

    // PDG ID.
    _PdgId = aTrack->GetDefinition()->GetPDGEncoding();

    // Global time.
    _globalTime = aTrack->GetGlobalTime();

    // Compute the step midpoint.
    G4ThreeVector posVec = (0.5 * (aStep->GetPreStepPoint()->GetPosition() + aStep->GetPostStepPoint()->GetPosition()));
    _position[0] = posVec[0];
    _position[1] = posVec[1];
    _position[2] = posVec[2];
}

void HitContribution::printOut(std::ostream& os) {
    os << _trackID << '\t' << _edep << '\t' << _PdgId << '\t' << _globalTime << std::endl;
}

G4int HitContribution::getTrackID() const {
    return _trackID;
}

G4double HitContribution::getEdep() const {
    return _edep;
}

void HitContribution::incrEdep(G4double incr) {
    _edep += incr;
}

G4int HitContribution::getPDGID() const {
    return _PdgId;
}

G4double HitContribution::getGlobalTime() const {
    return _globalTime;
}

void HitContribution::setMinTime(G4double new_time) {
    if (new_time < _globalTime) {
        _globalTime = new_time;
    }
}

const float* HitContribution::getPosition() const {
    return _position;
}
