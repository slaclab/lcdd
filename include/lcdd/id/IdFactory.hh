#ifndef LCDD_ID_IDFACTORY_HH_
#define LCDD_ID_IDFACTORY_HH_ 1

// LCDD
#include "IdVec.hh"
#include "IdSpec.hh"

// STL
#include <iostream>
#include <vector>

// LCDD
class Segmentation;

// Geant4
class G4Step;
class G4VPhysicalVolume;

// LCDD
class SensitiveDetector;

/**
 * @brief Produces IDs from step information.
 * @note It can also convert from an unpacked IdVec to a 64 bit packed ID.
 */
class IdFactory {
public:

    typedef unsigned int Bits;

    static const Bits MASK_ON;

private:

    /**
     * Class constructor.  Should not be instantiated.
     */
    IdFactory() {
    }

    /**
     * Class destructor.
     */
    virtual ~IdFactory() {
    }

public:

    /*
     * Create an Id64bit from the input IdVec and its matching specification.
     * @param[in] idvec  The vector of field values.
     * @param[in] idspec The identifier specification.
     */
    static Id64bit createIdentifier(const IdVec& idvec, IdSpec* idspec);

    /**
     * Create an IdVec ordered by the SD's idspec, or an empty vec if the SD does not have one.
     * @param[in] aStep A G4Step object.
     * @param[in] sd    The SensitiveDetector object.
     * @return The vector of ID field values.
     */
    static IdVec createOrderedIdVec(G4Step* aStep, const SensitiveDetector* sd);

private:

    /*
     * Make bit mask of a certain length.
     * @param[in] len The length of mask
     */
    static inline Bits makeBitMask(IdField::SizeType len);

    /**
     * Check that the given value does not overflow the mask.
     * @return If overflow, then returns the bits outside the mask else returns 0.
     */
    static inline Bits checkOverflow(Id64bit::ElementType field_val, Bits mask);

    /**
     * Lookup a bin value by field name in the Segmentation.
     * @param[in] segmentation The Segmentation object.
     * @param[in] field_name   The name of the field.
     * @return The index of the field in the Segmentation.
     */
    static int findFieldIdxInSegmentation(Segmentation* segmentation, const std::string& fieldName);

    /**
     * Check if the volume list has a PhysVolId with the given label.
     * @param[in] pvs       The list of volumes.
     * @param[in] fieldName The name of the field.
     * @return True if there is a PhysVolId with given field name in the list; false if not.
     */
    static bool hasPhysVolId(const std::vector<G4VPhysicalVolume*>& pvs, const std::string& fieldName);

    /**
     * Lookup a field value by name from the a list of volumes.
     * @param[in] pvs       The list of volumes.
     * @param[in] fieldName The name of the field.
     */
    static int findIdInPhysVols(const std::vector<G4VPhysicalVolume*>& pvs, const std::string& fieldName);
};

#endif
