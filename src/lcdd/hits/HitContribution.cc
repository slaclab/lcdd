#include "lcdd/hits/HitContribution.hh"

// Geant4
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

HitContribution::HitContribution() :
        _trackID(0), _edep(0), _PdgId(0), _globalTime(0) {
    ;
}

HitContribution::HitContribution(G4int trackID, G4double edep, G4int PDGID, G4double globalTime) :
        _trackID(trackID), _edep(edep), _PdgId(PDGID), _globalTime(globalTime) {
    ;
}

HitContribution::~HitContribution() {
    ;
}

HitContribution::HitContribution(int trackID, const G4Step* aStep) {
    // Get the track.
    const G4Track* track = aStep->GetTrack();

    _trackID = trackID;

    // Set edep according to type of track.
    //if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    //    _edep = track->GetTotalEnergy();
    //} else {
    _edep = aStep->GetTotalEnergyDeposit();
    //}

    // PDG ID.
    _PdgId = track->GetDefinition()->GetPDGEncoding();

    // Global time.
    _globalTime = track->GetGlobalTime();

    // Compute the step midpoint.
    G4ThreeVector posVec = (0.5 * (aStep->GetPreStepPoint()->GetPosition() + aStep->GetPostStepPoint()->GetPosition()));
    _position[0] = posVec[0];
    _position[1] = posVec[1];
    _position[2] = posVec[2];
}

HitContribution::HitContribution(const G4Step* aStep) {
    // Get the track.
    const G4Track* track = aStep->GetTrack();

    // Get the track information.
    //TrackInformation* trackInfo = static_cast<TrackInformation*>(track->GetUserInformation());

    // Get the track ID.
    //if (trackInfo) {
    //    _trackID = trackInfo->getOriginalTrackID();
    //}
    _trackID = track->GetTrackID();

    // Set edep according to type of track.
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        _edep = track->GetTotalEnergy();
    } else {
        _edep = aStep->GetTotalEnergyDeposit();
    }

    // PDG ID.
    _PdgId = track->GetDefinition()->GetPDGEncoding();

    // Global time.
    _globalTime = track->GetGlobalTime();

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
