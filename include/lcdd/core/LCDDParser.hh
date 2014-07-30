#ifndef LCDD_CORE_LCDDPARSER_HH_
#define LCDD_CORE_LCDDPARSER_HH_ 1

// GDML
#include "Saxana/SAXProcessor.h"
#include "Saxana/ProcessingConfigurator.h"

class G4VPhysicalVolume;

/**
 * @brief The parser for reading LCDD XML files into Geant4.
 */
class LCDDParser {

private:

    /**
     * Class constructor, which is private because this class
     * is accessed as a singleton.
     */
    LCDDParser();

public:

    /**
     * Class destructor.
     */
    virtual ~LCDDParser();

    /**
     * Get the static instance of this class.
     */
    static LCDDParser* instance();

    /**
     * Initialize the parser and build the geometry.
     * @return The geometry's world volume.
     */
    G4VPhysicalVolume* construct();

    /**
     * Set the URI of the LCDD or GDML file to build.
     * @param[in] URI The URI of the LCDD file.
     */
    void setURI(std::string URI);

    /**
     * Set the name of the GDML setup to load.
     * @param[in] setupName The name of the setup.
     * @warning Currently ignored by the parser.
     */
    void setSetupName(std::string setupName);

    /**
     * Set the version.
     * @param[in[ version The version.
     * @warning Not sure what this does!
     */
    void setVersion(std::string version);

    /**
     * Get the URI parameter value.
     * @return The current URI.
     */
    const std::string& URI();

    /**
     * Get the current setup name.
     * @return The current setup name.
     */
    const std::string& setupName();

    /**
     * Get the current version.
     * @return The current version.
     */
    const std::string& version();

    /**
     * Check if the current setup is valid.
     * @return True if valid; false if not.
     */
    bool isValidSetup();

private:

    /**
     * End of build hook.  Calls Finalize method of the SAX processor.
     */
    void finalize();

    /**
     * Initialize the XML parser.  This is just a wrapped for initializeParser.
     */
    void initialize();

    /**
     * Initialize the parser.
     */
    void initializeParser();

    /**
     * Add the subscriber for handling LCDD extension elements on the volume tags.
     */
    void addVolumeExtendedSubscriber();

    /**
     * Set all parser parameters.
     * @param[in] URI       The location of the geometry file.
     * @param[in] setupName The setup name.
     * @param[in] version   The version.
     */
    void setupParserConfig(const std::string& URI, const std::string& setupName, const std::string& version);

    /**
     * This sets up the parser configuration from the current instance variables.
     */
    void setupParserConfig();

private:

    SAXProcessor _sxp;
    ProcessingConfigurator _config;

    std::string _URI;
    std::string _setupName;
    std::string _version;

    bool _initialized;
    bool _constructed;
    bool _setURI;

    G4VPhysicalVolume* _world;

    static LCDDParser* _instance;

};
// class

#endif // header
