#ifndef LCDD_GEANT4_PHYSVOLID_HH_
#define LCDD_GEANT4_PHYSVOLID_HH_ 1

// STL
#include <vector>
#include <string>

/**
 * @brief Physical volume IDs that are attached to G4VPhysicalVolume objects.
 */
class PhysVolId {

public:
    typedef int ValueType;
    typedef std::vector<PhysVolId> PhysVolIds;

public:

    /**
     * Class constructor.
     * @param[in] val The value of the ID.
     * @param[in] fld The name of the ID.
     */
    PhysVolId(ValueType val, std::string fld);

    /**
     * Class destructor.
     */
    virtual ~PhysVolId();

public:

    /**
     * Get the value of the ID.
     * @return The value of the ID.
     */
    ValueType getValue() const;

    /**
     * Get the name of the field.
     * @return The name of the field.
     */
    const std::string& getFieldName() const;

    /**
     * Compare this PhysVolId to another based on their values.
     * @return True if ID values are equal; false if not.
     */
    bool operator==(const PhysVolId& right);

    /**
     * Compare this PhysVolId to a value.
     * @return True if value is equal to this ID; false if not.
     */
    bool operator==(ValueType vt);

private:

    ValueType _value;
    std::string _fieldName;
};

#endif
