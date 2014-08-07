#ifndef LCDD_GEANT4_LCDDHEADERRECORD_HH_
#define LCDD_GEANT4_LCDDHEADERRECORD_HH_ 1

// STL
#include <string>
#include <iostream>

/**
 * @brief This is the header record for an LCDD geometry.
 * @todo Move code to source file.
 */
class LCDDHeaderRecord {

public:

    /**
     * Class constructor.
     */
    LCDDHeaderRecord();

    /**
     * Class destructor.
     */
    virtual ~LCDDHeaderRecord();

public:

    /**
     * Set the name of the detector.
     * @param[in] dn The name of the detector.
     */
    void setDetectorName(const std::string& dn);

    /**
     * Set the version of the detector.
     * @param[in] dv The detector version.
     */
    void setDetectorVersion(const std::string& dv);

    /**
     * Set the URL of the input LCDD file.
     * @param[in] u The URL of the input file.
     */
    void setDetectorUrl(const std::string& u);

    /**
     * Set the author name.
     * @param[in] an The author name.
     */
    void setAuthorName(const std::string& an);

    /**
     * Set the generator name.
     * @param[in] gn The generator name.
     */
    void setGeneratorName(const std::string& gn);

    /**
     * Set the generator version.
     * @param[in] gv The generator version.
     */
    void setGeneratorVersion(const std::string& gv);

    /**
     * Set the generator checksum.
     * @param[in] c The generator checksum.
     */
    void setGeneratorChecksum(const std::string& c);

    /**
     * Set the generator input file.
     * @param[in] gurl The generator file.
     */
    void setGeneratorFile(const std::string& gurl);

    /**
     * Set the author email.
     * @param[in] ae The author email.
     */
    void setAuthorEmail(const std::string& ae);

    /**
     * Set the comment.
     * @param[in] c The comment.
     */
    void setComment(const std::string& c);

    /**
     * Set the checksum.
     * @param[in] c The checksum.
     */
    void setChecksum(const std::string& c);

    /**
     * Get the detector name.
     * @return The detector name.
     */
    const std::string& getDetectorName() const;

    /**
     * Get the detector version.
     * @return The detector version.
     */
    const std::string& getDetectorVersion() const;

    /**
     * Get the detector URL.
     * @return The detector URL.
     */
    const std::string& getDetectorUrl() const;

    /**
     * Get the comment.
     * @return The comment.
     */
    const std::string& getComment() const;

    /**
     * Get the author name.
     * @return The author name.
     */
    const std::string& getAuthorName() const;

    /**
     * Get the author email.
     * @return The author email.
     */
    const std::string& getAuthorEmail() const;

    /**
     * Get the generator name.
     * @return The generator name.
     */
    const std::string& getGeneratorName() const;

    /**
     * Get the generator version.
     * @return The generator version.
     */
    const std::string& getGeneratorVersion() const;

    /**
     * Get the generator file name.
     * @return The generator file name.
     */
    const std::string& getGeneratorFile() const;

    /**
     * Get the generator checksum.
     * @return The generator checksum.
     */
    const std::string& getGeneratorChecksum() const;

    /**
     * Print out the header information.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    std::ostream& printOut(std::ostream &os);

private:

    std::string _detectorName;
    std::string _detectorVersion;
    std::string _detectorUrl;
    std::string _generatorName;
    std::string _generatorVersion;
    std::string _generatorFile;
    std::string _generatorChecksum;
    std::string _authorName;
    std::string _authorEmail;
    std::string _comment;
};

#endif
