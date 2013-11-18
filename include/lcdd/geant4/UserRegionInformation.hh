//$Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/geant4/UserRegionInformation.hh,v 1.4 2013-11-14 00:47:20 jeremy Exp $

#ifndef LCDD_GEANT4_USERREGIONINFORMATION_HH
#define LCDD_GEANT4_USERREGIONINFORMATION_HH 1

// Geant4
#include "G4VUserRegionInformation.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "globals.hh"

// STL
#include <string>

/**
 * @brief Implements the G4VUserRegionInformation interface.
 */
class UserRegionInformation: public G4VUserRegionInformation {

public:

    /**
     * Class constructor.
     */
    UserRegionInformation() :
            _storeSecondaries(false), _killTracks(false) {
    }

    /**
     * Class destructor.
     */
    virtual ~UserRegionInformation() {
    }

public:

    /**
     * Set whether secondary tracks will be stored in this region.
     * @param[in] b The store secondaries setting.
     */
    void setStoreSecondaries(bool b) {
        _storeSecondaries = b;
    }

    /**
     * Get store secondaries setting which determines if secondary tracks are stored in this region.
     * @return The store secondaries setting.
     */
    bool getStoreSecondaries() const {
        return _storeSecondaries;
    }

    /**
     * Set parameter to kill tracks after their first step into the region.
     * @param[in] killTracks The kill tracks setting.
     */
    void setKillTracks(bool killTracks) {
        _killTracks = killTracks;
    }

    /**
     * Get the kill tracks setting.
     * @return The kill tracks setting.
     */
    bool getKillTracks() const {
        return _killTracks;
    }

    /**
     * Set the energy threshold.
     * @param[in] t The energy threshold.
     */
    void setThreshold(double t) {
        _threshold = t;
    }

    /**
     * Get the energy threshold.
     * @return The energy threshold.
     */
    double getThreshold() const {
        return _threshold;
    }

    /**
     * Print out the region information.
     * @todo Implement this method.
     */
    void Print() const {
    }

public:

    /**
     * A utility method for getting the region information from a track.
     * @param[in] aTrack A G4Track object.
     * @return The region information.
     */
    static inline UserRegionInformation* getRegionInformation(const G4Track* aTrack) {
        return static_cast<UserRegionInformation*>(aTrack->GetLogicalVolumeAtVertex()->GetRegion()->GetUserInformation());
    }

    /**
     * A utility method for getting the region information from a step point.
     * @param[in] aStepPoint A G4StepPoint object.
     * @return The region information.
     */
    static UserRegionInformation* getRegionInformation(const G4StepPoint* aStepPoint) {
        return static_cast<UserRegionInformation*>(aStepPoint->GetPhysicalVolume()->GetLogicalVolume()->GetRegion()->GetUserInformation());
    }

private:

    bool _storeSecondaries;
    bool _killTracks;
    double _threshold;
};

#endif
