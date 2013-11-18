// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/bfield/RZFieldMap.hh,v 1.5 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_BFIELD_RZFIELDMAP_HH
#define LCDD_BFIELD_RZFIELDMAP_HH 1

// Geant4
#include "G4MagneticField.hh"

// LCDD
#include "RZBData.hh"

// STL
#include <iostream>
#include <vector>

/**
 * @brief Magnetic field in RZ defined by rows of RZBData objects.
 */
class RZFieldMap: public G4MagneticField {

public:

    /**
     * Class constructor.
     * @param[in] numBinsR  The number of bins in R.
     * @param[in] numBinsZ  The number of bins in Z.
     * @param[in] gridSizeR The size of a cell in R.
     * @param[in] gridSizeZ The size of a cell in Z.
     * @param[in] fieldData A list of RZBData forming the B-field grid.
     */
    RZFieldMap(int numBinsR, int numBinsZ, double gridSizeR, double gridSizeZ, std::vector<RZBData> fieldData);

    /**
     * Class destructor.
     */
    virtual ~RZFieldMap();

public:

    /**
     * Implementation of G4MagneticField::Initialize.
     * @param[in]  Point  A point in global coordinates.
     * @param[out] Bfield The B-field values at the point.
     */
    void GetFieldValue(const double Point[3], double *Bfield) const;

private:

    /**
     * Initialize the data arrays.
     */
    void initializeArrays();

    /**
     * Fill the internal data arrays from the list of RZBData objects.
     * @param[in] fieldData The list of RZBData points.
     */
    void fillArrays(std::vector<RZBData> fieldData);

    /**
     * Delete the arrays containg the field data.
     */
    void deleteArrays();

private:

    int _numBinsR;
    int _numBinsZ;

    double _gridSizeR;
    double _gridSizeZ;

    double _maxR;
    double _maxZ;

    double** _BrArray;
    double** _BzArray;
};

#endif
