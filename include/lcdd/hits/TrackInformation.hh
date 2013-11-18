// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/hits/TrackInformation.hh,v 1.9 2013-11-14 00:47:20 jeremy Exp $
#ifndef LCDD_HITS_TRACKINFORMATION_HH
#define LCDD_HITS_TRACKINFORMATION_HH 1

// Geant4
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Allocator.hh"

/**
 * @brief Implements the G4VUserTrackInformation interface.
 * @todo Move code to source file.
 */
class TrackInformation: public G4VUserTrackInformation {

public:

    /**
     * Tracking status flag.
     */
    enum ETrackingStatus {
        eNone, eInTrackingRegion, eInNontrackingRegion
    };

public:

    /**
     * Class constructor.
     */
    TrackInformation();

    /**
     * Class destructor.
     */
    virtual ~TrackInformation();

    /**
     * Copy constructor from the information of another track.
     */
    TrackInformation(const G4Track* aTrack);

    /**
     * Copy constructor from another track information object.
     */
    TrackInformation(const TrackInformation* aTrackInfo);

    /**
     * Custom new operator.
     */
    inline void *operator new(size_t);

    /**
     * Custom delete operator.
     */
    inline void operator delete(void *aTrackInfo);

    /**
     * Overloaded assignment operator for copying.
     */
    TrackInformation& operator =(const TrackInformation& right);

    /**
     * Overloaded equals operator.
     */
    inline int operator ==(const TrackInformation& right) const;

    /**
     * Print out the track information.
     * @todo Implement this method.
     */
    virtual void Print() const;

    /**
     * Get the string of the status.
     * @return The tracking status string.
     */
    const std::string& getTrackingStatusString() const;

    /**
     * Get the original track ID.
     * @return The original track ID.
     */
    G4int getOriginalTrackID() const;

    /**
     * Get the original tracking status.
     * @return The original tracking status.
     */
    ETrackingStatus getOriginalTrackingStatus() const;

    /**
     * Get the tracking status.
     * @return The tracking status.
     */
    ETrackingStatus getTrackingStatus() const;

    /**
     * Check if there is a hit on the track.
     * @return True if this is a hit on the track; false if not.
     */
    bool hasTrackerHit() const;

    /**
     * Set has tracker hit.
     * @param[in] hasHit Set has tracker hit.
     */
    void setHasTrackerHit(bool hasHit = true);

    /**
     * Set the track ID.
     * @param[in] id The track ID.
     */
    void setTrackID(G4int id);

    /**
     * Set the tracking status.
     * @param[in] st The tracking status.
     */
    void setTrackingStatus(ETrackingStatus st);

    /**
     * Set the original tracking status.
     * @param[in] st The tracking status.
     */
    void setOriginalTrackingStatus(ETrackingStatus st);

    /**
     * Set vertex not endpoint of parent.
     * @param[in] val Vertex not endpoint setting.
     */
    void setVertexIsNotEndpointOfParent(bool val = true);

    /**
     * Get vertex not endpoint of parent setting.
     * @return True if vertex not endpoint of parent; false if not.
     */
    bool getVertexIsNotEndpointOfParent() const;

    /**
     * Set backscatter setting.
     * @param[in] val The backscatter setting.
     */
    void setBackscatter(bool val = true);

    /**
     * Get the backscatter setting.
     * @return The backscatter setting.
     */
    bool getBackscatter() const;

    /**
     * Set the below threshold setting.
     * @param[in] val The below threshold setting.
     */
    void setBelowThreshold(bool val = true);

    /**
     * Get the below threshold setting.
     * @return True if below threshold; false if not.
     */
    bool getBelowThreshold() const;

    /**
     * Get the track information from a track.
     * @param[in] aTrack The G4Track object.
     * @return The track information of the track.
     */
    static TrackInformation* getTrackInformation(const G4Track* aTrack);

    /**
     * Get the track information a step.
     * @param[in] aStep The G4Step object.
     * @return The track information from the step.
     */
    static TrackInformation* getTrackInformation(const G4Step* aStep);

    /**
     * Convert a tracking status to a string.
     * @param[in] ts The tracking status.
     * @return The tracking status string.
     */
    static const std::string& getTrackingStatusString(ETrackingStatus ts);

private:

    /**
     * Set parameters from another track information object.
     * @param[in] srcTrackInfo The source track information.
     * @param[in] trgtTrkInfo  The target track information.
     */
    static void setFromTrackInformation(const TrackInformation* srcTrkInfo, TrackInformation* trgtTrkInfo);

    /**
     * Reset this track information to defaults.
     */
    void setDefaults();

private:

    G4int _originalTrackID;

    ETrackingStatus _trackingStatus;
    ETrackingStatus _originalTrackingStatus;

    G4bool _hasTrackerHit;

    G4bool _vertexIsNotEndpointOfParent;
    G4bool _backscatter;
    G4bool _belowThreshold;
};

extern G4Allocator<TrackInformation> TrackInformationAllocator;

/**
 * Implementation of custom new operator.
 */
inline void* TrackInformation::operator new(size_t) {
    void* aTrackInfo;
    aTrackInfo = (void*) TrackInformationAllocator.MallocSingle();
    return aTrackInfo;
}

/**
 * Implementation of custom delete operator.
 */
inline void TrackInformation::operator delete(void *aTrackInfo) {
    TrackInformationAllocator.FreeSingle((TrackInformation*) aTrackInfo);
}

#endif
