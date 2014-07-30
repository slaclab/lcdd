#ifndef LCDD_DETECTORS_STEPREADOUT_HH_
#define LCDD_DETECTORS_STEPREADOUT_HH_ 1

// Geant4
#include "G4ThreeVector.hh"
#include "G4TouchableHandle.hh"

// STL
#include <vector>

// Geant4
class G4VPhysicalVolume;
class G4VSensitiveDetector;
class G4Step;
class G4StepPoint;
class G4Region;
class G4Material;
class G4LogicalVolume;
class G4VSolid;
class G4Track;

// LCDD
class TrackInformation;
class UserRegionInformation;

/**
 * @brief Static utility functions to access derived information of a G4Step object.
 * @note The only cached data member of this class is the step pointer.
 */
class StepReadout {

public:

    /**
     * Class constructor.
     */
    StepReadout();

    /**
     * Class destructor.
     */
    virtual ~StepReadout();

public:

    /**
     * Set the G4Step object of this StepReadout.
     * @param[in] s The G4Step object to be cached.
     */
    void setStep(G4Step* s);

    /**
     * Get the cached G4Step object.
     * @return The cached G4Step object.
     */
    G4Step* step() const;

    /**
     * Check if this object has a cached G4Step.
     * @return True if there is a cached G4Step; false if not.
     */
    bool hasStep() const;

    /**
     * Get the pre step point of the current step.
     * @return The pre step point of the current step.
     */
    G4StepPoint* pre() const;

    /**
     * Get the post step point of the current step.
     * @return The post step point of the current step.
     */
    G4StepPoint* post() const;

    /**
     * Get the physical volume associated with the pre step point.
     * @return The physical volume from the pre step point.
     */
    G4VPhysicalVolume* prePV() const;

    /**
     * Get the physical volume associated with the post step point.
     * @return The physical volume from the post step point.
     */
    G4VPhysicalVolume* postPV() const;

    /**
     * Get the solid associated with the pre step point.
     * @return The solid from the pre step point.
     */
    G4VSolid* preSolid() const;

    /**
     * Get the solid associated with the post step point
     * @return The solid from the post step point.
     */
    G4VSolid* postSolid() const;

    /**
     * Get the logical volume from the pre step point.
     * @return The logical volume from the pre step point.
     */
    G4LogicalVolume* preLV() const;

    /**
     * Get the logical volume from the post step point.
     * @return The logical volume from the post step point.
     */
    G4LogicalVolume* postLV() const;

    /**
     * Get the material from the pre step point.
     * @return The material from the pre step point.
     */
    G4Material* preMaterial() const;

    /**
     * Get the material from the post step point.
     * @return The material from post step point.
     */
    G4Material* postMaterial() const;

    /**
     * Get the region from the pre step point.
     * @return The region from the pre step point.
     */
    G4Region* preRegion() const;

    /**
     * Get the region from the post step point.
     * @return The region from the post step point.
     */
    G4Region* postRegion() const;

    /**
     * Get the center position of the volume pointed to by the touchable.
     * @return The position of the volume from the touchable.
     */
    G4ThreeVector volumePosition(G4TouchableHandle theTouchable) const;

    /**
     * Get the center position of the volume from the pre step point.
     * @return The center position of the volume from the pre step point.
     */
    G4ThreeVector preVolumePosition() const;

    /**
     * Get the center position of the volume from the post step point.
     * @return The center position of the volume from the post step point.
     */
    G4ThreeVector postVolumePosition() const;

    /**
     * Get the sensitive detector from the pre step point.
     * @return The sensitive detector from the pre step point.
     */
    G4VSensitiveDetector* preSD() const;

    /**
     * Get the sensitive detector from the post step point.
     * @return The sensitive detector from the post step point.
     */
    G4VSensitiveDetector* postSD() const;

    /**
     * Get the sensitive detector from the step point.
     * @return The sensitive detector from the step point.
     */
    G4VSensitiveDetector* getSD(G4StepPoint*) const;

    /**
     * Check if the pre and post step point sensitive detectors are the same.
     * @return True if the SDs are the same; false if not.
     */
    bool hasSameSD() const;

    /**
     * Get the energy deposition of the step.
     * @return The energy deposition of the step.
     */
    double edep() const;

    /**
     * Get the track from the step.
     * @return The track from the step.
     */
    G4Track* track() const;

    /**
     * Get the global time of the track.
     * @return The global time of the track.
     */
    double globalTime() const;

    /**
     * Get the ID of the track.
     * @return The ID of the track.
     */
    int trackID() const;

    /**
     * Get the momentum of the track.
     * @return The momentum of the track.
     */
    G4ThreeVector momentum() const;

    /**
     * Get the track information.
     * @return The track information.
     */
    //TrackInformation* trackInformation() const;

    /**
     * Get the position of the pre step point.
     * @return The position of the pre step point.
     */
    G4ThreeVector prePosition() const;

    /**
     * Get the mid position of the step.
     * @return The mid position of the step.
     */
    G4ThreeVector midPosition() const;

    /**
     * Get the position of the post step point.
     * @return The position of the post step point.
     */
    G4ThreeVector postPosition() const;

    /**
     * Get the momentum at the pre step point.
     * @return The momentum at the pre step point.
     */
    G4ThreeVector preMomentum() const;

    /**
     * Get the momentum of the post step point.
     * @return The momentum at the post step point.
     */
    G4ThreeVector postMomentum() const;

    /**
     * The mean of the pre and post momenta.
     * @return The mean of the pre and post momenta.
     */
    G4ThreeVector meanMomentum() const;

    /**
     * Get the touchable handle from the pre step point.
     * @return The touchable handle from the pre step point.
     */
    G4TouchableHandle preTouchableHandle() const;

    /**
     * Get the touchable handle from the post step point.
     * @return The touchable handle from the post step point.
     */
    G4TouchableHandle postTouchableHandle() const;

    /**
     * Check if the current step points to a Geantino particle.
     * @return True if the current step points to a Geantino; false if not.
     */
    bool isGeantino();

protected:

    // cached step
    G4Step* _step;

    // vector = [0,0,0]
    const G4ThreeVector _origin;
};

#endif
