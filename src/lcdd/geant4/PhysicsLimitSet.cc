#include "lcdd/geant4/PhysicsLimitSet.hh"

// Geant4
#include "G4Track.hh"

/* Code for any particle. */
const PhysicsLimitSet::ParticleType PhysicsLimitSet::ANY_PARTICLE = "*";

/* Code for no limit, as -1 is never a valid limit. */
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::LIMIT_NOT_SET = -1;

/* Keys to limit value maps for each parameter. */
const PhysicsLimitSet::LimitNameKeyType PhysicsLimitSet::STEP_LENGTH_MAX_KEY = "step_length_max";
const PhysicsLimitSet::LimitNameKeyType PhysicsLimitSet::TRACK_LENGTH_MAX_KEY = "track_length_max";
const PhysicsLimitSet::LimitNameKeyType PhysicsLimitSet::TIME_MAX_KEY = "time_max";
const PhysicsLimitSet::LimitNameKeyType PhysicsLimitSet::EKIN_MIN_KEY = "ekin_min";
const PhysicsLimitSet::LimitNameKeyType PhysicsLimitSet::RANGE_MIN_KEY = "range_min";

/* Default values for limits.  Taken from G4UserLimit ctor default args. */
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::STEP_LENGTH_MAX_DEFAULT = DBL_MAX;
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::TRACK_LENGTH_MAX_DEFAULT = DBL_MAX;
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::TIME_MAX_DEFAULT = DBL_MAX;
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::EKIN_MIN_DEFAULT = 0.;
const PhysicsLimitSet::LimitValueType PhysicsLimitSet::RANGE_MIN_DEFAULT = 0.;

PhysicsLimitSet::PhysicsLimitSet(const G4String& name) :
        G4UserLimits("G4LimitSet"), _name(name) {
    _limitsMap[STEP_LENGTH_MAX_KEY] = LimitMap();
    _limitsMap[TRACK_LENGTH_MAX_KEY] = LimitMap();
    _limitsMap[TIME_MAX_KEY] = LimitMap();
    _limitsMap[EKIN_MIN_KEY] = LimitMap();
    _limitsMap[RANGE_MIN_KEY] = LimitMap();
}

PhysicsLimitSet::~PhysicsLimitSet() {
}

G4double PhysicsLimitSet::GetMaxAllowedStep(const G4Track& aTrack) {
    double maxStepLength = getLimitForParticle(STEP_LENGTH_MAX_KEY, aTrack);
    return maxStepLength == LIMIT_NOT_SET ? STEP_LENGTH_MAX_DEFAULT : maxStepLength;
}

G4double PhysicsLimitSet::GetUserMaxTrackLength(const G4Track& aTrack) {
    double maxTrackLength = getLimitForParticle(TRACK_LENGTH_MAX_KEY, aTrack);
    return maxTrackLength == LIMIT_NOT_SET ? TRACK_LENGTH_MAX_DEFAULT : maxTrackLength;
}

G4double PhysicsLimitSet::GetUserMaxTime(const G4Track& aTrack) {
    double maxTime = getLimitForParticle(TIME_MAX_KEY, aTrack);
    return maxTime == LIMIT_NOT_SET ? TIME_MAX_DEFAULT : maxTime;
}

G4double PhysicsLimitSet::GetUserMinEkine(const G4Track& aTrack) {
    double minEkine = getLimitForParticle(EKIN_MIN_KEY, aTrack);
    return minEkine == LIMIT_NOT_SET ? EKIN_MIN_DEFAULT : minEkine;
}

G4double PhysicsLimitSet::GetUserMinRange(const G4Track& aTrack) {
    double minRange = getLimitForParticle(RANGE_MIN_KEY, aTrack);
    return minRange == LIMIT_NOT_SET ? RANGE_MIN_DEFAULT : minRange;
}

const PhysicsLimitSet::ParticleType PhysicsLimitSet::getParticleType(const G4Track& aTrack) {
    return aTrack.GetDefinition()->GetParticleName();
}

void PhysicsLimitSet::setLimitForParticle(LimitNameType limitName, ParticleType particleType, LimitValueType limitValue) {
    if (_limitsMap.find(limitName) != _limitsMap.end()) {
        _limitsMap[limitName][particleType] = limitValue;
    } else {
        G4Exception("", "", FatalException, "Invalid limits map.");
    }
}

PhysicsLimitSet::LimitValueType PhysicsLimitSet::getLimitForParticle(LimitNameType limitName, ParticleType particleType) {
    //std::cout << "G4LimitSet::getLimitForParticle()" << std::endl;
    //std::cout << "limitName, particleType: " << limitName << " " << particleType << std::endl;
    LimitValueType limitValue = 0;
    if (_limitsMap.find(limitName) != _limitsMap.end()) {
        if (_limitsMap[limitName].find(particleType) != _limitsMap[limitName].end()) {
            limitValue = _limitsMap[limitName][particleType];
        } else {
            if ((_limitsMap[limitName].find(ANY_PARTICLE) != _limitsMap[limitName].end())) {
                limitValue = _limitsMap[limitName][ANY_PARTICLE];
            } else {
                limitValue = LIMIT_NOT_SET;
            }
        }
    } else {
        G4Exception("", "", FatalException, "Invalid limits map.");
    }
    //std::cout << "limitValue: " << limitValue << std::endl;
    return limitValue;
}

PhysicsLimitSet::LimitValueType PhysicsLimitSet::getLimitForParticle(LimitNameType limitName, const G4Track& aTrack) {
    return getLimitForParticle(limitName, getParticleType(aTrack));
}

//void PhysicsLimitSet::setName(const G4String& n)
//{
//    _name = n;
//}

G4String& PhysicsLimitSet::getName() {
    return _name;
}

