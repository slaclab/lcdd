#ifndef LCDD_SCHEMA_COMMENTTYPE_HH_
#define LCDD_SCHEMA_COMMENTTYPE_HH_ 1

// STL
#include <string>

/**
 * @brief The CommentType from the schema.
 */
class CommentType {
public:

    /**
     * Class destructor.
     */
    CommentType() {
    }

    /**
     * Class destructor.
     */
    virtual ~CommentType() {
    }

    /**
     * Set the comment contents.
     * @param c The comment.
     */
    void set_comment(const std::string& c) {
        _comment = c;
    }

    /**
     * Get the comment.
     * @return The comment.
     */
    const std::string& get_comment() const {
        return _comment;
    }

private:

    std::string _comment;

};

#endif
