#ifndef LCDD_ID_IDSPEC_HH_
#define LCDD_ID_IDSPEC_HH_ 1

// LCDD
#include "IdField.hh"

// std
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

/**
 * @brief A list of IdField objects that together constitute an identifier specification.
 * @todo Move code to source file.
 */
class IdSpec {

public:

    typedef unsigned int SizeType;
    typedef std::vector<IdField*> IdFields;

public:

    /**
     * Class constructor.
     */
    IdSpec();

    /**
     * Class destructor.
     */
    virtual ~IdSpec();

    /**
     * Set the name.
     * @param[in] n The name.
     */
    void setName(const std::string& n);

    /**
     * Set the total bit length.
     * @param[in] st The bit length.
     */
    void setBitLength(SizeType st);

    /**
     * Get the bit length.
     * @return The bit length of the ID.
     */
    SizeType getBitLength() const;

    /**
     * Get the name.
     * @return The name.
     */
    const std::string& getName() const;

    /**
     * Get the number of fields.
     * @return The number of fields.
     */
    SizeType getNumFields() const;

    /**
     * Add a field to the end of the list.
     * @param[in] f The IdField to add.
     */
    void addIdField(IdField* f);

    /**
     * Get a field by name.
     * @param[in] n The field name.
     * @return The field with name or 0 if doesn't exist.
     */
    IdField* getIdField(const std::string& n) const;

    /**
     * Get a field by index.
     * @param[in] st The index of the field.
     * @return The field at index.
     */
    IdField* getIdField(SizeType st) const;

    /**
     * Get the list of fields.
     * @return The list of fields.
     */
    const IdFields& getIdFields() const;

    /**
     * Get an iterator pointing to the first IdField.
     * @return An iterator pointing to the first IdField.
     */
    IdFields::const_iterator IdFieldsBegin() const;

    /**
     * Get an iterator pointing to the end of the IdField list.
     * @return An iterator pointing to the end of the IdField list.
     */
    IdFields::const_iterator IdFieldsEnd() const;

    /**
     * Get the field's description.
     * @return The description of the field.
     * @todo Is this by field or the whole IdSpec?
     */
    std::string getFieldDescription();

    /**
     * Clear the list of fields.
     * @todo Check if this can be removed or made private.
     */
    void clear();

    /**
     * Print out the IdSpec information.
     * @param[in] os The output stream.
     */
    void printOut(std::ostream& os) const;

private:

    /**
     * Delete the fields of this ID.
     */
    void deleteIdFields();

private:
    std::string _name;
    SizeType _bitLength;
    IdFields _idFields;
};

#endif
