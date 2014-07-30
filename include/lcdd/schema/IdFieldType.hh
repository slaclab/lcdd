#ifndef LCDD_SCHEMA_IDFIELDTYPE_HH_
#define LCDD_SCHEMA_IDFIELDTYPE_HH_ 1

// STL
#include <string>

/**
 * @brief The IdFieldType from the schema.
 */
class IdFieldType {
public:

    /**
     * Class constructor.
     */
    IdFieldType() {
    }

    /**
     * Class destructor.
     */
    virtual ~IdFieldType() {
    }

public:

    /**
     * Set the label of the field.
     * @param l The label of the field.
     */
    void set_label(const std::string& l) {
        _label = l;
    }

    /**
     * Set the starting position of the field.
     * @param s The starting position of the field.
     */
    void set_start(const std::string& s) {
        _start = s;
    }

    /**
     * Set the bit length of the field.
     * @param l The bit length of the field.
     */
    void set_length(const std::string& l) {
        _length = l;
    }

    /**
     * Set whether the field is signed or not.
     * @param s Set value for field sign.
     */
    void set_signed(const std::string& s) {
        _signed = s;
    }

    /**
     * Get the label of the field.
     * @return The label of the field.
     */
    const std::string& get_label() {
        return _label;
    }

    /**
     * Get the starting bit position of the field.
     * @return The starting bit position.
     */
    const std::string& get_start() {
        return _start;
    }

    /**
     * Get the length of the field.
     * @return The length of the field.
     */
    const std::string& get_length() {
        return _length;
    }

    /**
     * Get whether the field is signed or not.
     * @return The signage of the field.
     */
    const std::string& get_signed() {
        return _signed;
    }

private:
    std::string _label;
    std::string _start;
    std::string _length;
    std::string _signed;
};

#endif
