#ifndef LCDD_ID_IDVEC_HH_
#define LCDD_ID_IDVEC_HH_ 1

// LCDD
#include "Id64bit.hh"

// std
#include <vector>

/**
 * @brief A vector of int values representing an unpacked ID.
 *
 * @note
 *
 * Inspired by ATLAS's ExpandedIdentifier from repository file:
 *
 * DetectorDescription/Identifier/Identifier-00-06-10/Identifier/ExpandedIdentifier.h
 */
class IdVec {

public:
    typedef int ElementType;
    typedef std::vector<ElementType> ElementVector;
    typedef std::vector<ElementType>::size_type SizeType;

public:

    /**
     * Class constructor.
     */
    IdVec();

    /**
     * Class destructor.
     */
    virtual ~IdVec();

    /**
     * Clear the fields from the vector.
     * @todo Check if this is used anyplace in the code base.
     */
    void clear();

    /**
     * Push a value onto the vector.
     * @param[in] et The new value to add.
     */
    void addFieldValue(ElementType et);

    /**
     * Get a value by index.
     * @param[in] idx The field index.
     * @return The field value.
     */
    ElementType getFieldValue(SizeType idx) const;

    /**
     * Set a value by index.
     * @param[in] idx The index.
     * @param[in] et  The new value.
     */
    void setFieldValue(SizeType idx, ElementType et);

    /**
     * Overloaded operator for accessing value by index.
     * @param[in] idx The index.
     * @return The value at index.
     */
    ElementType operator [](SizeType idx) const;

    /**
     * Get an iterator pointing to the first field value.
     * @return An iterator pointing to the first field value.
     */
    ElementVector::const_iterator getFieldsBegin() const;

    /**
     * Get an iterator pointing to the end of the field value list.
     * @return An iterator pointing to the end of the field value list.
     */
    ElementVector::const_iterator getFieldsEnd() const;

    /**
     * Get the size of this vector.
     * @return The size of this vector.
     */
    SizeType size() const;

private:

    ElementVector _fields;
};

#endif
