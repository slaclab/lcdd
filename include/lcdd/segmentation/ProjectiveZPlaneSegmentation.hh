#ifndef LCDD_SEGMENTATION_PROJECTIVEZPLANESEGMENTATION_HH_
#define LCDD_SEGMENTATION_PROJECTIVEZPLANESEGMENTATION_HH_ 1

// LCDD
#include "lcdd/segmentation/ProjectiveSegmentation.hh"

// Geant4
#include "globals.hh"

/**
 * @brief This is a projective Segmentation using Z and phi.
 * @note This class uses Z from current volume rather than the cylindrical radius.
 * @todo Document this class better.
 */
class ProjectiveZPlaneSegmentation: public ProjectiveSegmentation {

public:

    /**
     * Class constructor.
     * @param[in] ntheta The number of theta bins per 180 degrees.
     * @param[in] nphi   The number of phi bins per 360 degrees.
     */
    ProjectiveZPlaneSegmentation(int ntheta, int nphi);

    /**
     * Class destructor.
     */
    virtual ~ProjectiveZPlaneSegmentation();

protected:

    /**
     * Get the radius of the step from the cylinder at that point.
     * @return The radius at the step.
     */
    virtual double getRadius(const G4Step* aStep);

    /**
     * Get the Z of the step from the cylinder at that point.
     * @return The Z at the step.
     */
    virtual double getZ(const G4Step* aStep);

    //virtual double getRadius(const G4StepPoint* aPreStepPoint);
    //virtual double getZ(const G4StepPoint* aPreStepPoint);
};

#endif
