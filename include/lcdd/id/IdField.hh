#ifndef LCDD_ID_IDFIELD_HH_
#define LCDD_ID_IDFIELD_HH_ 1

// STL
#include <string>

/**
 * @brief An individual field in an identifier specification, including
 * start position, length, label and signed flag.
 */
class IdField {
public:

    typedef unsigned short int SizeType;

public:

    /**
     * Class constructor.
     */
    IdField();

    /**
     * Class destructor.
     */
    virtual ~IdField();

    /**
     * Fully qualified constructor.
     * @param[in] label    The label of the field.
     * @param[in] start    The start, numbered from 0.
     * @param[in] length   The length.
     * @param[in] isSigned Flag indiciating if signed or not.
     */
    IdField(const std::string& label, SizeType start, SizeType length, bool isSigned);

    /**
     * Set the label on the field.
     * @param[in] l The label.
     */
    void setLabel(const std::string& l);

    /**
     * Set the starting bit position of the field.
     * @param[in] st The startng bit position.
     */
    void setStart(SizeType st);

    /**
     * Set the length of the field.
     * @param[in] st The length of the field.
     */
    void setLength(SizeType st);

    /**
     * Set if the field is signed or not.
     * @param[in] s The signed flag.
     */
    void setSigned(bool s);

    /**
     * Get the label.
     * @return The label.
     */
    const std::string& getLabel();

    /**
     * Get the starting bit position.
     * @return The starting position.
     */
    SizeType getStart();

    /**
     * Get the length.
     * @return The length.
     */
    SizeType getLength();

    /**
     * Get the signed flag.
     * @return True if field is signed; false if not.
     */
    bool getSigned();

private:

    std::string _label;
    SizeType _start;
    SizeType _length;
    bool _isSigned;
};

#endif
