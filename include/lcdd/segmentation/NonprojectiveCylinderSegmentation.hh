#ifndef LCDD_SEGMENTATION_G4NONPROJECTIVECYLINDERSEGMENTATION_
#define LCDD_SEGMENTATION_G4NONPROJECTIVECYLINDERSEGMENTATION_ 1

// LCDD
#include "lcdd/segmentation/Segmentation.hh"

/**
 * @brief A Segmentation class that implements a nonprojective cylinder.
 * @todo This class needs much better documentation.  Much of the computational code is a black box.
 */
class NonprojectiveCylinderSegmentation: public Segmentation {

public:

    /**
     * Class constructor.
     * @param[in] gridSizePhi The grid size in phi (radians).
     * @param[in] gridSizeZ   The grid size in Z (mm).
     */
    NonprojectiveCylinderSegmentation(double gridSizePhi, double gridSizeZ);

    /**
     * Class destructor.
     */
    virtual ~NonprojectiveCylinderSegmentation();

public:

    /**
     * Compute the global hit position from a step.
     * @param[in] aStep The G4Step object.
     * @return The global hit position for the step.
     */
    G4ThreeVector getGlobalHitPosition(const G4Step* aStep);

    /**
     * Compute the global hit position a step point.
     * @param[in] aPreStepPoint The G4StepPoint object.
     * @return The global hit position for the step point.
     */
    //G4ThreeVector getGlobalHitPos(const G4StepPoint* aPreStepPoint);
    /**
     * Compute bin values from a step.
     * @param[in] aStep The G4Step object.
     */
    void setBins(const G4Step* aStep);

    /**
     * Compute bin values from a step point.
     * @param[in] aPreStepStep The G4StepPoint object.
     */
    //void setBins(const G4StepPoint* aPreStepPoint);
    G4ThreeVector getLocalHitPos(const G4Step* aStep);

    /**
     * @todo This method should not exist.
     */
    G4ThreeVector getLocalHitPos(const G4StepPoint* aPreStepPoint);

    /**
     * Check if a G4VSolid is valid for this segmentation.
     * @return True if solid is valid; false if not.
     */
    bool isValidSolid(G4VSolid*);

protected:

    /**
     * Set the valid bin names for this Segmentation.
     */
    void setBinNames();

private:

    /**
     * Computes the delta phi from a step.
     * @param[in] aStep A G4Step object.
     * @return The delta phi.
     */
    double computeDeltaPhi(const G4Step* aStep);

    /**
     * Compute the phi bin from a step.
     * @param[in] aStep A G4Step object.
     * @return The phi bin.
     */
    int computeBinPhi(const G4Step* aStep);

    /**
     * Compute the Z bin from a step.
     * @param[in] aStep A G4Step object.
     * @return The Z bin.
     * @todo Remove this method.
     */
    int computeBinZ(const G4ThreeVector& localStepPos);

    /**
     * Compute the phi bin from a step point.
     * @param[in] aPreStepPoint The G4StepPoint object.
     * @return The phi bin.
     * @todo Remove this method.
     */
    int computeBinPhi(const G4StepPoint* aPreStepPoint);

    /**
     * Compute the delta phi from a step point.
     * @param[in] aPreStepPoint The G4StepPoint object.
     * @return The delta phi.
     */
    double computeDeltaPhi(const G4StepPoint* aPreStepPoint);

private:

    double _gridSizePhi;
    double _gridSizeZ;
};

#endif
