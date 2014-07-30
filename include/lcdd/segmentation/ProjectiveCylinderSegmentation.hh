#ifndef LCDD_SEGMENTATION_PROJECTIVECYLINDERSEGMENTATION_HH_
#define LCDD_SEGMENTATION_PROJECTIVECYLINDERSEGMENTATION_HH_ 1

// LCDD
#include "lcdd/segmentation/ProjectiveSegmentation.hh"

// Geant4
#include "globals.hh"

/**
 * @brief Segmentation that divides cylinders into theta and phi bins.
 */
class ProjectiveCylinderSegmentation: public ProjectiveSegmentation {

public:

    /**
     * Class constructor.
     * @param[in] ntheta Number of cells in theta.
     * @param[in] nphi   Number of cells in phi.
     */
    ProjectiveCylinderSegmentation(G4int ntheta, G4int nphi);

    /**
     * Class destructor.
     */
    virtual ~ProjectiveCylinderSegmentation();

    /**
     * Check whether a Geant4 solid is valid for this Segmentation.
     * @param[in] s The G4VSolid object.
     * @return True if input sold is valid for the Segmentation; false if not.
     */
    bool isValidSolid(G4VSolid* s);

protected:

    /**
     * Get the radial position of the solid pointed to by the step.
     * @param[in] aStep The G4Step object.
     * @return The radial position of the step's cell.
     */
    double getRadius(const G4Step* aStep);

    /**
     * Get the Z coordinate of a cell from the step.
     * @param[in] aStep The G4Step object.
     * @return The Z coordinate of the step's cell.
     */
    double getZ(const G4Step* aStep);

    /**
     * Get the radial position of the cell pointed to by the step point.
     * @param[in] aPreStepPoint The G4StepPoint object.
     * @return The radial position of the step point's cell.
     */
    //double getRadius(const G4StepPoint* aPreStepPoint);
    /**
     * Get the Z coordinate of a cell from a step point.
     * @param[in] aPreStepPoint The G4PreStepPoint object.
     * @return The Z coordinate of the step point's cell.
     */
    //double getZ(const G4StepPoint* aPreStepPoint);
};

#endif
