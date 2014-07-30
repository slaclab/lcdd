#ifndef LCDD_SEGMENTATION_G4GRIDXYZSEGMENTATION_HH_
#define LCDD_SEGMENTATION_G4GRIDXYZSEGMENTATION_HH_ 1

// LCDD
#include "lcdd/segmentation/Segmentation.hh"

// Geant4
#include "globals.hh"

/**
 * @brief A Segmentation that defines a grid in a combination of X, Y or Z coordinates.
 * @brief This class performs calculations to divide a box-like volume into a uniform, 3D grid of cells.
 */
class GridXYZSegmentation: public Segmentation {

public:

    /**
     * Class constructor.
     * @param[in] gridSizeX The grid size in X.
     * @param[in] gridSizeY The grid size in Y.
     * @param[in] gridSizeZ The grid size in Z.
     */
    GridXYZSegmentation(double gridSizeX, double gridSizeY, double gridSizeZ);

    /**
     * Class destructor.
     */
    virtual ~GridXYZSegmentation();

public:

    /**
     * Compute the global hit position from a step.
     * @param[in] aStep The G4Step object.
     * @return The global hit position.
     */
    G4ThreeVector getGlobalHitPosition(const G4Step* aStep);

    /**
     * Compute the bin values from a step.
     * @param[in] aStep The G4Step object.
     */
    void setBins(const G4Step* aStep);

    // DEPRECATED
    //G4ThreeVector getGlobalHitPosPreStep(const G4StepPoint* aPreStepPoint);

    /**
     * Compute the local hit position from a local step position.
     * @param[in] localStepPos The local step position.
     * @return The local hit position.
     */
    G4ThreeVector getLocalHitPos(const G4ThreeVector& localStepPos);

protected:

    /**
     * Set the valid bin names for this Segmentation.
     */
    void setBinNames();

    /**
     * Compute X bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The X bin value.
     */
    int computeBinX(const G4ThreeVector& localStepPos);

    /**
     * Compute Y bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The Y bin value.
     */
    int computeBinY(const G4ThreeVector& localStepPos);

    /**
     * Compute Z bin value from a local coordinate.
     * @param[in] localStepPos The local step position.
     * @return The Z bin value.
     */
    int computeBinZ(const G4ThreeVector& localStepPos);

    /**
     * Compute a cell center X coordinate from a bin value.
     * @param[in] The bin value.
     * @return The corresponding 1D cell coordinate value.
     */
    double computeDimX(int bin);

    /**
     * Compute a cell center Y coordinate from a bin value.
     * @param[in] The bin value.
     * @return The corresponding 1D cell coordinate value.
     */
    double computeDimY(int bin);

    /**
     * Compute a cell center Z coordinate from a bin value.
     * @param[in] The bin value.
     * @return The corresponding 1D cell coordinate value.
     */
    double computeDimZ(int bin);

private:

    double _gridSizeX;
    double _gridSizeY;
    double _gridSizeZ;
};

#endif
