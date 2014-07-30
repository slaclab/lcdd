#ifndef LCDD_SEGMENTATION_SEGMENTATION_HH_
#define LCDD_SEGMENTATION_SEGMENTATION_HH_ 1

// Geant4
#include "G4ThreeVector.hh"
#include "G4Step.hh"

// STL
#include <iostream>
#include <vector>

/**
 * @brief Base class for calorimeter virtual segmentation implementations.
 * @todo Add method setVolume(G4LogicalVolume*) for setting up segmentation from the current G4Step.
 */
class Segmentation {
public:

    /**
     * Defines the basic type of Segmentation, e.g. projective or non-projective.
     */
    enum EType {
        eProjective = 1, eNonprojective
    };

    /**
     * Type definition for list of bin names.
     */
    typedef std::vector<std::string> BinNames;

public:

    /**
     * Class Constructor.
     * @param[in] segType The type of Segmentation.
     * @param[in] nbins   The number of bins defined by this Segmentation.
     */
    Segmentation(EType segType, int nbins = 2);

    virtual ~Segmentation();

public:

    /**
     * Compute the global hit position from a step using this Segmentation.
     * @param[in] aStep The Geant4 step.
     * @return The hit's global position.
     */
    virtual G4ThreeVector getGlobalHitPosition(const G4Step* aStep) = 0;

    /**
     * Set the identifier bin values from a step.
     * @param[in] aStep The Geant4 step.
     */
    virtual void setBins(const G4Step* aStep) = 0;

    /*
     * Check whether the solid is valid for this segmentation.
     * @return True if solid is valid; false if not.
     */
    virtual bool isValidSolid(G4VSolid*);

    /**
     * @deprecated Only used by G4OpticalCalorimeter.
     * @todo n     Move to G4OpticalCalorimeter.
     * @warning    Dummy method only.  Specific Segmentation types must implement.
     */
    G4ThreeVector getLocalHitPosition(const G4ThreeVector& localStepPos);

    /**
     * Get the type of this segmentation.
     * @return The Segmentation type as an enum.
     */
    EType getType();

    /**
     * Get a string for this Segmentation type.
     * @return The Segmentation type as a string.
     */
    const G4String& getTypeString();

    /**
     * Get a bin value from an index.
     * @param[in] idx The index of the bin.
     * @return The bin value.
     * @todo Change this method's name to "getBinValue".
     */
    int getBin(int idx);

    /**
     * Get the name of a bin from an index.
     * @param[in] idx The bin index.
     * @return The name of the bin.
     */
    const std::string& getBinName(int idx);

    /**
     * Get the number of bins defined by this Segmentation.
     * @return The number of bins.
     */
    int getNumberOfBins();

    /**
     * Get a list of current bin values.
     * @return A list of bin values.
     */
    const std::vector<int>& getBins();

    /**
     * Get a list of bin names.
     * @return The list of bin names.
     */
    const std::vector<std::string>& getBinNames();

    /**
     * Print this object's bin values to an output stream.
     * @param[in] os The output stream.
     */
    void printOutBins(std::ostream& os);

protected:

    /**
     * Set the valid bin names for this Segmentation.
     * @note This should only be called once.
     */
    virtual void setBinNames() = 0;

    /**
     * Add a bin name to the end of the list.
     * @param[in] The name of the bin.
     */
    void addBinName(const std::string& binName);

    /**
     * Set the bin value.
     * @param[in] binIdx The index of the bin.
     * @param[in] binVal The value of the bin.
     * @todo Change method name to "setBinValue".
     */
    void setBin(int binIdx, int binVal);

    /**
     * Print the bin values to an output stream.
     * @param[in] os   The output stream.
     * @param[in] bins The list of bin values.
     */
    static void printOutBins(std::ostream& os, const std::vector<int>& bins);

    /**
     * Compute the bin given a coordinate in one dimension.
     * @param[in] localDim The 1D coordinate value.
     * @param[in] gridDim  The dimension of the readout grid.
     * @return The value of the bin at that coordinate.
     */
    static int computeBin(double localDim, double gridDim);

    /**
     * Compute the coordinate of a cell center at a given a bin value.
     * @param[in] bin  The bin value.
     * @param[in] incr The grid size.
     * @return The coordinate of the cell center.
     */
    static double computeDim(const int &bin, const double &incr);

protected:

    /** The current bin values. */
    std::vector<int> _bins;

    /** The list of bin names. */
    BinNames _binNames;

    /** The number of bins. */
    int _numBins;

    /** The type of Segmentation. */
    EType _type;
};

#endif
