// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/segmentation/ProjectiveSegmentation.hh,v 1.2 2013-11-14 00:47:23 jeremy Exp $
#ifndef LCDD_SEGMENTATION_PROJECTIVESEGMENTATION_HH
#define LCDD_SEGMENTATION_PROJECTIVESEGMENTATION_HH 1

#include "lcdd/segmentation/Segmentation.hh"

#include "globals.hh"

/**
 * @brief The base class for Segmentation classes with projective readouts.
 * @todo Should this class be pure virtual or have a protected constructor?
 */
class ProjectiveSegmentation: public Segmentation {

public:

    /**
     * Class constructor.
     * @param[in] ntheta The number of cells in theta per 180 degrees.
     * @param[in] nphi   The number of cells in phi per 360 degrees.
     */
    ProjectiveSegmentation(int ntheta, int nphi);

    /**
     * Class destructor.
     */
    virtual ~ProjectiveSegmentation();

public:

    /**
     * Compute the global hit position from the step.
     * @param[in] aStep The G4Step object.
     * @return The global hit position at the step.
     */
    G4ThreeVector getGlobalHitPosition(const G4Step* aStep);

    /**
     * Compute the bin values from a step.
     * @param[in] aStep The G4Step object.
     */
    void setBins(const G4Step* aStep);

    //G4ThreeVector getGlobalHitPos(const G4StepPoint* aPreStepPoint);
    //void setBins(const G4StepPoint* aPreStepPoint);

protected:

    /**
     * Get the valid bin names for this Segmentation.
     */
    void setBinNames();

    /**
     * Get the number of theta cells.
     * @return The number of theta cells.
     */
    int getNtheta() const;

    /**
     * Get the number of phi cells.
     * @return The number of phi cells.
     */
    int getNphi() const;

    /**
     * Compute the theta bin from a 3D position.
     * @return The theta bin.
     */
    int getThetaBin(const G4ThreeVector& globalStepPos);

    /**
     * Compute the phi bin from a 3D position.
     * @return The phi bin.
     */
    int getPhiBin(const G4ThreeVector& globalStepPos);

    /**
     * Compute a theta coordinate from a bin value.
     * @return The theta coordinate.
     */
    double getThetaDim(const int &thetaBin) const;

    /**
     * Compute a phi coordinate from a bin value.
     * @return The phi coordinate.
     */
    double getPhiDim(const int &phiBin) const;

    /**
     * Compute a theta coordinate from a step.
     * @param[in] aStep The G4Step object.
     * @return The theta coordinate.
     */
    double getThetaDim(const G4Step* aStep);

    /**
     * Compute a phi coordinate from a step.
     * @param[in] aStep The G4Step object.
     * @return The phi coordinate.
     */
    double getPhiDim(const G4Step* aStep);

    /**
     * Get the radius at the step, taken from the geometric cylinder layer at that point.
     * @return The radius at the step from the geometric cylinder.
     */
    virtual double getRadius(const G4Step* aStep);

    /**
     * Get the Z at the step, taken from the layer of the geometric cylinder layer at that point.
     * @return The Z at the step from the geometric layer.
     */
    virtual double getZ(const G4Step* aStep);

    // dim from prestep
    //double getThetaDim(const G4StepPoint* aPreStepPoint);
    // dim from prestep point:
    //double getPhiDim(const G4StepPoint* aPreStepPoint);
    //virtual double getRadius(const G4StepPoint* aPreStepPoint);
    //virtual double getZ(const G4StepPoint* aPreStepPoint);

private:

    /**
     * Compute the size of the bins from the input parameters.
     */
    void computeDivisions();

private:
    int _ntheta, _nphi;
    double _divTheta, _divPhi;
};

#endif
