#ifndef LCDD_DETECTORS_READOUTUTIL_HH_
#define LCDD_DETECTORS_READOUTUTIL_HH_ 1

// LCDD
#include "lcdd/core/LCDDProcessor.hh"

// Geant4
#include "G4VSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Tubs.hh"
#include "G4StepPoint.hh"
#include "G4NavigationHistory.hh"
#include "G4ThreeVector.hh"

// STL
#include <vector>

/**
 * @brief Static utility functions for use by detector and readout classes.
 */
class ReadoutUtil {

private:

    /**
     * Class constructor, which is private because class should not be instantiated.
     */
    ReadoutUtil() {
    }

    /**
     * Class destructor, which is private because class is never instantiated.
     */
    virtual ~ReadoutUtil() {
    }

public:

    /**
     * Compute the mean of two vectors e.g. the mid-point between them.
     * @param[in] vec1 The first 3-vector.
     * @param[in] vec2 The second 3-vector.
     * @return The mean of the two vectors.
     */
    static G4ThreeVector computeThreeVectorMean(const G4ThreeVector& vec1, const G4ThreeVector& vec2);

    /**
     * Compute the midpoint of the step using the pre and post step points.
     * @param[in] aStep The G4Step object.
     * @return The midpoint of the step.
     */
    static G4ThreeVector computeMidPos(const G4Step* aStep);

    /**
     * Compute the distance between two points.
     * @param[in] vec1 The first point.
     * @param[in] vec2 The second point.
     * @return The distance between the two points.
     */
    static G4double computeDistance(const G4ThreeVector& vec1, const G4ThreeVector& vec2);

    /**
     * Compute the distance between the pre and post step points of a step.
     * @param[in] aStep The G4Step object.
     * @return The length of the step.
     */
    static G4double computeDistance(const G4Step* aStep);

    /**
     * Get the solid at the step point.
     * @param[in] aStepPoint The G4StepPoint object.
     * @return The solid at the step point.
     */
    static G4VSolid* getSolidFromStepPoint(const G4StepPoint* aStepPoint);

    //static G4TouchableHandle getTouchableFromStep(const G4Step* aStep);

    /**
     * Transform the given point into the global reference frame of the solid at the step point.
     * @param[in] aStepPoint The G4StepPoint object.
     * @return The transformed point based on the volume's coordinate system.
     */
    static G4ThreeVector getVolumeGlobalPosition(const G4StepPoint* aStepPoint, const G4ThreeVector& pnt);

    /**
     * Get the global position of the volume at the step point.
     * @param[in] aStepPoint The G4StepPoint object.
     * @return The position of the volume at the step point.
     */
    static G4ThreeVector getVolumeGlobalPosition(const G4StepPoint* aStepPoint);

    /**
     * Get the Tubs solid from the step.
     * @param[in] aStep The G4Step object.
     * @return The Tubs solid at the step
     */
    static const G4Tubs* getTubs(const G4Step* aStep);

    /**
     * Get the Tubs solid from the step point.
     * @param[in] aStep The G4Step object.
     * @return The Tubs solid at the step point.
     */
    static const G4Tubs* getTubs(const G4StepPoint* aStepPoint);

    /**
     * Get the midpoint between the inner and outer radii of the Tubs.
     * @param[in] tubs The Tubs solid.
     * @return The Tubs midpoint.
     */
    static double computeTubsMidRadius(const G4Tubs* tubs);

    /**
     * Get the midpoint between the inner and outer radii of the Tubs at the step.
     * @param[in] aStep The G4Step object.
     * @return The Tubs midpoint at the step.
     */
    static double computeTubsMidRadius(const G4Step* aStep);

    /**
     * Get the thickness of the Tubs which is the distance between the inner and outer radii.
     * @param[in] tubs The Tubs solid.
     * @return The thickness of the Tubs solid.
     */
    static double getTubsThickness(const G4Tubs* tubs);

    /**
     * Transform local point to global reference frame of the step.
     * @param[in] localPos The local position to transform.
     * @return The position transformed from local to global coordinates.
     */
    static G4ThreeVector transformLocalToGlobal(const G4Step* aStep, const G4ThreeVector& localPos);

    /**
     * Transform global point to local reference frame of the step.
     * @param[in] globalPos The global position to transform.
     * @return The position transformed from global to local coordinates.
     */
    static G4ThreeVector transformGlobalToLocal(const G4Step* aStep, const G4ThreeVector& globalPos);

    /**
     * Get the number of the volume at the given depth.
     * @param[in] historyDepth The depth into the touchable history.
     * @return The volume number.
     */
    static int getVolumeNumber(G4TouchableHandle theTouchable, int historyDepth = -1);

    /**
     * Get a list of PhysicalVolumes at the step.
     * @param[in] aStep The G4Step object.
     * @return The list of PhysicalVolumes at the step.
     */
    static std::vector<G4VPhysicalVolume*> getPhysVolList(G4Step* aStep);

    /**
     * Check if the step has a Geantino particle.
     * @param[in] aStep The G4Step object.
     * @return True if geantino is particle of step's track; false if not.
     */
    static bool isGeantino(G4Step* aStep);

    /**
     * @todo Remove this method.
     * @deprecated
     */
    static double computeTubsMidRadius(const G4StepPoint* aStepPoint);

    /**
     * @todo Remove this method.
     * @deprecated
     */
    static G4ThreeVector transformLocalToGlobal(const G4StepPoint* aPreStepPoint, const G4ThreeVector& localPos);

    /**
     * @todo Remove this method.
     * @deprecated
     */
    static G4ThreeVector transformGlobalToLocal(const G4StepPoint* aPreStepPoint, const G4ThreeVector& globalPos);

public:

    static const double PI;
};

#endif
