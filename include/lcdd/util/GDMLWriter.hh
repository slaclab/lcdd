#ifndef LCDD_UTIL_GDMLWRITER_HH_
#define LCDD_UTIL_GDMLWRITER_HH_ 1

// STL
#include <string>
#include <vector>

/**
 * @brief Wrapper for the GDML package's writer.
 */
class GDMLWriter {
private:
    GDMLWriter() {
    }

public:

    /**
     * Write the current geometry to an output file.
     * @param[in] fileName The name of the output file.
     */
    static void writeCurrentGeometry(const std::string& fileName);

    /**
     * Write the list of volumes to an output file.
     * @param[in] fileName The name of the output file.
     * @param[in] volumes  The list of volumes.
     */
    static void writeCurrentGeometry(const std::string& fileName, std::vector<std::string> volumes);
};

#endif
