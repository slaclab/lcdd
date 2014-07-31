/**
 * @mainpage Linear Collider Detector Description (LCDD) Documentation
 *
 * @par
 * LCDD is a framework for description of detector geometries and associated information
 * at runtime using a XML language and parser.
 */
#include "lcdd/core/LCDDDetectorConstruction.hh"

// LCDD
#include "lcdd/core/LCDDParser.hh"
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/core/LCDDMessenger.hh"
#include "lcdd/core/LCDDObjectStoreInspector.hh"
#include "lcdd/util/GDMLWriterMessenger.hh"
#include "lcdd/core/GeometryManager.hh"

// Geant4
#include "G4VPhysicalVolume.hh"
#include "G4UImanager.hh"
#include "G4Timer.hh"

// std
#include <cassert>

LCDDDetectorConstruction::LCDDDetectorConstruction() :
        _world(0) {
    // LCDD messenger
    _messenger = new LCDDMessenger();

    // writer messenger
    _writerMessenger = new GDMLWriterMessenger();

    // setup geo manager
    GeometryManager::instance();

    // setup parser if not already
    LCDDParser::instance();

    _inspector = new LCDDObjectStoreInspector();
}

LCDDDetectorConstruction::~LCDDDetectorConstruction() {
    delete _inspector;
    delete _writerMessenger;
    delete _messenger;
}

G4VPhysicalVolume* LCDDDetectorConstruction::Construct() {
    // start build timer
    G4Timer geoTimer;
    geoTimer.Start();

    G4cout << "Started geometry construction timer." << G4endl;

    // get geometry from the global parser instance, which will die on failure
    G4VPhysicalVolume* pv = LCDDParser::instance()->construct();

    // set world ptr
    setWorldVolume(pv);

    // stop build timer and print
    geoTimer.Stop();
    G4cout << "Geometry construction time: " << geoTimer << G4endl;

    return pv;
}

void LCDDDetectorConstruction::setWorldVolume(G4VPhysicalVolume *pv) {
    if (pv == 0) {
        G4Exception("", "", FatalException, "PhysVol points to null.");
    }

    _world = pv;
}

G4VPhysicalVolume* LCDDDetectorConstruction::getWorldVolume() {
    return _world;
}

