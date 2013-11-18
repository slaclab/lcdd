// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/segmentation/GlobalGridXYSegmentation.hh,v 1.2 2013-11-14 00:47:23 jeremy Exp $

#ifndef LCDD_SEGMENTATION_GLOBALGRIDXYSEGMENTATION_HH
#define LCDD_SEGMENTATION_GLOBALGRIDXYSEGMENTATION_HH 1

// LCDD
#include "lcdd/segmentation/Segmentation.hh"

// Geant4
#include "globals.hh"

/**
 * @brief An XY grid Segmentation in global coordinates.
 * @note This is a version of grid segmentation with binning on global coordinates.
 */
class GlobalGridXYSegmentation: public Segmentation {

public:

    /**
     * Class constructor.
     * @param[in] gridSizeX The grid size X.
     * @param[in] gridSizeY The grid size Y.
     */
    GlobalGridXYSegmentation(double gridSizeX, double gridSizeY);

    /**
     * Class destructor.
     */
    virtual ~GlobalGridXYSegmentation();

public:

    /**
     * Compute a global hit position from a G4Step.
     * @param[in] The G4Step object.
     * @return The cell global position.
     */
    G4ThreeVector getGlobalHitPosition(const G4Step* aStep);

    /**
     * Compute a local cell position from a local step position.
     * @param[in] localStepPos The local step position.
     * @return The local cell position.
     */
    //G4ThreeVector getLocalHitPos(const G4ThreeVector& localStepPos);
    /**
     * Compute the ID bin values from a step.
     * @param[in] aStep The G4Step object.
     */
    void setBins(const G4Step* aStep);

    /**
     * Set the bin names for this Segmentation.
     */
    void setBinNames();

private:

    /**
     * Compute the X bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The X bin value.
     */
    int computeBinX(const G4ThreeVector& localStepPos);

    /**
     * Compute the Y bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The Y bin value.
     */
    int computeBinY(const G4ThreeVector& localStepPos);

    /**
     * Compute the z bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The Z bin value.
     */
    int computeBinZ(const G4ThreeVector& localStepPos);

    /**
     * Compute the X coordinate from a bin value.
     * @param[in] The X bin value.
     * @return The X coordinate value.
     */
    double computeDimX(int bin);

    /**
     * Compute the Y coordinate from a bin value.
     * @param[in] The Y bin value.
     * @return The Y coordinate value.
     */
    double computeDimY(int bin);

    /**
     * Compute the Z coordinate from a bin value.
     * @param[in] The Z bin value.
     * @return The Z coordinate value.
     */
    double computeDimZ(int bin);

private:

    double _gridSizeX;
    double _gridSizeY;
    double _gridSizeZ;
};

#endif
