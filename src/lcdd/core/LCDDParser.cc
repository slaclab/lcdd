#include "lcdd/core/LCDDParser.hh"

// LCDD
#include "lcdd/bfield/FieldManager.hh"
#include "lcdd/subscribers/volumeExtendedSubscriber.hh"

// GDML
#include "G4Processor/GDMLProcessor.h"
#include "Saxana/SAXComponentFactoryTable.h"
#include "Saxana/RCObjectHandle.h"
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXSubscriberPool.h"

// Geant4
#include "G4VPhysicalVolume.hh"

extern "C" void LCDDLibLoad();

LCDDParser* LCDDParser::_instance = 0;

LCDDParser::LCDDParser() :
        _URI(""),
        _setupName("Default"),
        _version("1.0"),
        _initialized(false),
        _constructed(false),
        _setURI(false),
        _world(NULL) {
}

LCDDParser* LCDDParser::instance() {
    if (_instance == 0) {
        _instance = new LCDDParser();
    }
    return _instance;
}

LCDDParser::~LCDDParser() {
    finalize();
}

void LCDDParser::configure() {

    G4cout << "LCDD Setup:" << G4endl;
    G4cout << "  URI <" << _URI << ">" << G4endl;
    G4cout << "  SetupName <" << _setupName << ">" << G4endl;
    G4cout << "  Version <" << _version << ">" << G4endl;
    G4cout << G4endl;

    // Set the configuration values.
    _config.SetURI(_URI);
    _config.SetSetupVersion(_version);
    _config.SetSetupName(_setupName);

    // The the configuration of the parser.
    _sxp.Configure(&_config);
}

void LCDDParser::initialize() {
    // Not already initialized?
    if (!_initialized) {
        // Initialize the SAX parser.
        _sxp.Initialize();

        // Load the LCDD tag handlers.
        LCDDLibLoad();

        // Add the subscriber for the extended GDML volume tag.
        addVolumeExtendedSubscriber();

        // Set initialized to true.
        _initialized = true;
    } else {
        G4cerr << "WARNING: LCDDParser was already initialized!" << G4endl;
    }
}

G4VPhysicalVolume* LCDDParser::construct() {
    // Not already constructed?
    if (!_constructed) {

        // Initialize the parser.
        initialize();

        // Configure the parser with the setup parameters.
        configure();

        // Run the parser on the input document.
        _sxp.Run();

        // Get the world volume created by the parser.
        try {
            // Set the reference to the world volume.
            _world = (G4VPhysicalVolume*) GDMLProcessor::GetInstance()->GetWorldVolume();
        } catch (std::exception& e) {
            // Something went wrong in the detector construction.  Probably an invalid document.
            G4Exception("", "", FatalException, "Failed to get the world volume.");
        }

        // Setup the magnetic field manager.
        FieldManager::instance()->setup();

        // This method should only be called once.
        _constructed = true;
    } else {
        std::cerr << "WARNING: LCDD geometry was already constructed!" << std::endl;
    }

    // Return the world volume.
    return _world;
}

void LCDDParser::finalize() {
    _sxp.Finalize();
}

void LCDDParser::setURI(std::string URI) {
    _URI = URI;
    _setURI = true;
}

void LCDDParser::setSetupName(std::string setupName) {
    _setupName = setupName;
}

void LCDDParser::setVersion(std::string version) {
    _version = version;
}

bool LCDDParser::isValidSetup() {
    bool valid = true;
    if (!_setURI) {
        valid = false;
    }
    return valid;
}

void LCDDParser::addVolumeExtendedSubscriber() {
    RCObjectHandle<SAXSubscriber> obj;
    obj = new volumeExtendedSubscriber();
    SAXSubscriberPool* pool = const_cast<SAXSubscriberPool*>(_sxp.GetSubscriberPool());
    pool->AddSubscriber("volume", obj);
}
