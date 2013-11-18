#ifndef LCDD_SEGMENTATION_CELLREADOUT2DSEGMENTATION_HH
#define LCDD_SEGMENTATION_CELLREADOUT2DSEGMENTATION_HH 1

// LCDD
#include "lcdd/segmentation/Segmentation.hh"
#include "lcdd/segmentation/CellReadout2D.hh"

// Geant4
#include "G4ThreeVector.hh"

class G4Step;

/**
 * @brief Adapt a CellReadout2D object to the LCDD Segmentation interface.
 */
class CellReadout2DSegmentation: public Segmentation {

public:

    /**
     * Class constructor.
     * @param[in] cellSizeX The cell size X.
     * @param[in] cellSizeY The cell size Y.
     */
    CellReadout2DSegmentation(double cellSizeX, double cellSizeY);

    /**
     * Class destructor.
     */
    virtual ~CellReadout2DSegmentation();

    /**
     * Get the global cell center position from a step.
     * @param[in] The Geant4 step.
     * @return The cell's 3D position.
     */
    G4ThreeVector getGlobalHitPosition(const G4Step* step);

    /**
     * Compute the bin values from a Geant4 step.
     * @param[in] The G4Step object.
     */
    void setBins(const G4Step* step);

    /**
     * Set the bin names for this Segmentation.
     */
    void setBinNames();

    /**
     * Setup derived state of the Segmentation from a G4Step.
     * @param[in] The G4Step object.
     */
    void setup(const G4Step* step);

    /**
     * Convert local to readout coordinates.
     * @param[in] pos The local position.
     * @return The readout coordinates.
     */
    CellReadout::Position2D localToReadoutCoordinates(G4ThreeVector& pos);

    /**
     * Convert unsigned readout coordinates back to local.
     * @return The local coordinates converted from readout XY position.
     */
    G4ThreeVector readoutToLocalCoordinates(CellReadout::Position2D position);

private:

    CellReadout2D* _readout;
};

#endif
