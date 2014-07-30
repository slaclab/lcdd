#ifndef LCDD_ID_ID64BIT_HH_
#define LCDD_ID_ID64BIT_HH_ 1

// STL
#include <stdint.h>

/**
 * @brief A 64-bit ID composed of two 32-bit halves.
 */
class Id64bit {

public:

    /**
     * The type definition for a 32 bit half of the ID.
     */
    typedef int ElementType;

    /**
     * The type definition for the 64 bit value of this ID.
     */
    typedef uint64_t ValueType;

public:

    /**
     * Class constructor.
     */
    Id64bit();

    /**
     * Fully qualified class constructor.
     */
    Id64bit(ElementType id0, ElementType id1);

    /**
     * Copy constructor.
     */
    Id64bit(const Id64bit &right);

    /**
     * Class destructor.
     */
    virtual ~Id64bit();

    /**
     * Set the first 32 bits of the ID.
     * @param[id] id0 The first 32 bits of the ID.
     */
    void setId0(ElementType id0);

    /**
     * Set the second 32 bits of the ID.
     * @param[id] id1 The second 32 bits of the ID.
     */
    void setId1(ElementType id1);

    /**
     * Get the first 32 bits of the ID.
     * @return The first half of the ID.
     */
    ElementType getId0() const;

    /**
     * Get the second 32 bits of the ID.
     * @return The second half of the ID.
     */
    ElementType getId1() const;

    /**
     * Overloaded equals operator.
     */
    bool operator==(const Id64bit& right) const;

    /**
     * Get the value of the ID, defined as a 64-bit int.
     * @return The value of the ID.
     */
    ValueType getValue() const;

    /**
     * Set the current value by bit packing the 32-bit int values into a 64-bit value.
     */
    void encode();

    /**
     * Set to default values.
     */
    void resetIds();

private:
    ElementType _ids[2];
    ValueType _value;
};

#endif
