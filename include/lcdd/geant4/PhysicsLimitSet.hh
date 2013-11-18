// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/geant4/PhysicsLimitSet.hh,v 1.4 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_GEANT4_LIMITSET_HH
#define LCDD_GEANT4_LIMITSET_HH 1

// Geant4
#include "G4UserLimits.hh"
#include "globals.hh"

// STL
#include <map>
#include <string>

/**
 * @brief Looks up physics limits by particle type from the G4Track.
 */
class PhysicsLimitSet: public G4UserLimits {

public:

    typedef G4String ParticleType;
    typedef G4String LimitNameType;
    typedef G4double LimitValueType;

    typedef std::map<ParticleType, LimitValueType> LimitMap;
    typedef std::map<LimitNameType, LimitMap> LimitSetMap;
    typedef const G4String& LimitNameKeyType;

    static const ParticleType ANY_PARTICLE;

    static const LimitValueType LIMIT_NOT_SET;

    static const LimitNameKeyType STEP_LENGTH_MAX_KEY;
    static const LimitNameKeyType TRACK_LENGTH_MAX_KEY;
    static const LimitNameKeyType TIME_MAX_KEY;
    static const LimitNameKeyType EKIN_MIN_KEY;
    static const LimitNameKeyType RANGE_MIN_KEY;

    static const LimitValueType STEP_LENGTH_MAX_DEFAULT;
    static const LimitValueType TRACK_LENGTH_MAX_DEFAULT;
    static const LimitValueType TIME_MAX_DEFAULT;
    static const LimitValueType EKIN_MIN_DEFAULT;
    static const LimitValueType RANGE_MIN_DEFAULT;

public:

    /**
     * Class constructor.
     * @param[in] name The name of the PhysicsLimitSet.
     */
    PhysicsLimitSet(const G4String& name);

    /**
     * Class destructor.
     */
    virtual ~PhysicsLimitSet();

public:

    /**
     * Get the limit set map.
     * @return The limit set map.
     */
    const LimitSetMap& getLimitSetMap() const {
        return _limitsMap;
    }

    /**
     * Get the max allowed step length.
     * @param[in] track A G4Track object.
     * @return The max allowed step length (mm).
     */
    virtual G4double GetMaxAllowedStep(const G4Track& track);

    /**
     * Get the max length.
     * @param[in] track A G4Track object.
     * @return The max allowed track length (mm).
     */
    virtual G4double GetUserMaxTrackLength(const G4Track& track);

    /**
     * Get the max time.
     * @param[in] track A G4Track object.
     * @return The max allowed time for the track.
     */
    virtual G4double GetUserMaxTime(const G4Track& track);

    /**
     * Get the min kinetic energy.
     * @param[in] track A G4Track object.
     * @return The min kinetic energy.
     */
    virtual G4double GetUserMinEkine(const G4Track& track);

    /**
     * Get the min range.
     * @param[in] track A G4Track object.
     * @return The min range.
     */
    virtual G4double GetUserMinRange(const G4Track& track);

    /*
     * Set physics limits by particle type.
     */
    void setLimitForParticle(LimitNameType limitName, ParticleType particleType, LimitValueType limitValue);

    /**
     * Set the name of this PhysicsLimitSet.
     *
     */
    //void setName(const G4String& n);
    /**
     * Get the name of the PhysicsLimitSet.
     * @return The name of this PhysicsLimitSet.
     */
    G4String& getName();

private:

    /**
     * Get the limit value for a particular particle type.
     * @param[in]  limitName    The name of the limit type (1 of 5 valid types).
     * @param[in]  particleType The name of the Geant4 particle.
     * @return Value of the limit, or LIMIT_NOT_SET if no key exists and ANY_PARTICLE is also not set.
     */
    LimitValueType getLimitForParticle(LimitNameType limitName, ParticleType particleType = ANY_PARTICLE);

    /**
     * Get the limit value from a track.
     * @param[in] limitName The name of the limit.
     * @param[in] track     A G4Track object.
     */
    LimitValueType getLimitForParticle(LimitNameType limitName, const G4Track& track);

private:

    /**
     * Get the particle type from a track.
     * @param[in] track A G4Track object.
     * @return The particle type.
     */
    const ParticleType getParticleType(const G4Track& track);

protected:

    /** A map of limitName => particleName => limitValue */
    LimitSetMap _limitsMap;
    G4String _name;
};

#endif
