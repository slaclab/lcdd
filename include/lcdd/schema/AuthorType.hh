#ifndef LCDD_SCHEMA_AUTHORTYPE_HH_
#define LCDD_SCHEMA_AUTHORTYPE_HH_ 1

// STL
#include <string>

/**
 * @brief AuthorType from schema.
 */
class AuthorType {
public:

    /**
     * Class constructor.
     */
    AuthorType() {
    }

    /**
     * Class destructor.
     */
    virtual ~AuthorType() {
    }

    /**
     * Set the name of the author.
     * @param n The name string.
     */
    void set_name(const std::string& n) {
        _name = n;
    }

    /**
     * Set the email of the author.
     * @param o The email string.
     */
    void set_email(const std::string& o) {
        _email = o;
    }

    /**
     * Get the name of the author.
     * @return The name of the author.
     */
    const std::string& get_name() const {
        return _name;
    }

    /**
     * Get the email of the author.
     * @return The email of the author.
     */
    const std::string& get_email() const {
        return _email;
    }

private:

    std::string _name;
    std::string _email;
};

#endif
