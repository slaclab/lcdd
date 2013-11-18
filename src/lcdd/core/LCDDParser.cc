// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/core/LCDDParser.cc,v 1.5 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/core/LCDDParser.hh"
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
        _URI(""), _setupName(""), _version(""), _initialized(false), _constructed(false), _setURI(false) {
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

void LCDDParser::setupParserConfig() {
    setupParserConfig(_URI, _setupName, _version);
}

void LCDDParser::setupParserConfig(const std::string& URI, const std::string&, const std::string& version) {
    // settings from messenger commands
    std::cout << "LCDD URI <" << _URI << ">" << std::endl;
    //std::cout << "SetupName <" << m_setupName << ">" << std::endl;
    std::cout << "Version <" << _version << ">" << std::endl;

    // set configuration vals
    _config.SetURI(URI);
    //m_config.SetSetupName(setupName);
    _config.SetSetupVersion(version);

    // set config in parser
    _sxp.Configure(&_config);
}

void LCDDParser::initializeParser() {
    // standard SAX parser init
    _sxp.Initialize();

    // load custom LCDD tag handlers
    LCDDLibLoad();

    addVolumeExtendedSubscriber();
}

void LCDDParser::initialize() {
    if (!_initialized) {
        initializeParser();
        _initialized = true;
    }
}

G4VPhysicalVolume* LCDDParser::construct() {
    if (!_constructed) {

        // initialize
        initialize();

        // set GDML parser params from inst vars
        setupParserConfig();

        // run the parser
        _sxp.Run();

        // get world volume from GDML
        try {
            _world = (G4VPhysicalVolume*) GDMLProcessor::GetInstance()->GetWorldVolume();
        } catch (std::exception& e) {
            G4Exception("", "", FatalException, "Failed to get the world volume.");
        }

        // Setup magnetic field.
        FieldManager::instance()->setup();

        // This method should only be called once.
        _constructed = true;
    } else {
        std::cerr << "LCDD geometry was already constructed." << std::endl;
    }

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

const std::string& LCDDParser::URI() {
    return _URI;
}

const std::string& LCDDParser::setupName() {
    return _setupName;
}

const std::string& LCDDParser::version() {
    return _version;
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

