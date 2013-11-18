// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/bfield/FieldManager.cc,v 1.3 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/bfield/FieldManager.hh"
#include "lcdd/core/LCDDProcessor.hh"

FieldManager* FieldManager::_instance = 0;

FieldManager::~FieldManager() {
}

FieldManager* FieldManager::instance() {
    if (_instance == 0) {
        _instance = new FieldManager();
    }
    return _instance;
}

MagneticFieldOverlay* FieldManager::makeOverlay(std::vector<G4MagneticField*> fields) {
    MagneticFieldOverlay* overlay = new MagneticFieldOverlay();
    for (std::vector<G4MagneticField*>::const_iterator iter = fields.begin(); iter != fields.end(); iter++) {
        overlay->addMagneticField(*iter);
    }
    return overlay;
}

void FieldManager::setup() {
    // Pointer to the field which will be passed to Geant4.
    G4MagneticField* field = 0;

    // Setup only the global fields specified in global_field.
    if (_globalfields.size() != 0) {
        // Use specific list of global fields registered with LCDDFieldManager.
        field = setup(_globalfields);
    }
    // No global fields, so treat all fields registered with LCDDProcessor
    // as global.
    else {

        // Build a list of fields that were registered with the LCDDProcessor.
        std::vector<G4MagneticField*> fields;
        LCDDProcessor* proc = LCDDProcessor::instance();
        for (LCDDProcessor::MagneticFields::const_iterator iter = proc->getMagneticFieldsBegin(); iter != proc->getMagneticFieldsEnd(); iter++) {
            fields.push_back(iter->second);
        }

        // Setup fields from LCDDProcessor.
        field = setup(fields);
    }

    // Initialize the single or overlay field with Geant4.
    initialize(field);
}

G4MagneticField* FieldManager::setup(std::vector<G4MagneticField*> fields) {
    G4MagneticField* field = 0;
    //if (fields.size() == 0) {
    //  G4cerr << "LCDDFieldManager - No magnetic fields to setup." << G4endl;
    //}
    //else if (fields.size() == 1) {
    //  field = fields[0];
    //}
    //else {
    field = makeOverlay(fields);
    //}
    return field;
}

void FieldManager::initialize(G4MagneticField* field) {
    if (field != 0) {
        G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
        fieldMgr->SetDetectorField(field);
        fieldMgr->CreateChordFinder(field);
    }
}

void FieldManager::addGlobalField(G4MagneticField* f) {
    _globalfields.push_back(f);
}

void FieldManager::addField(G4MagneticField* f) {
    _allfields.push_back(f);
}

FieldManager::FieldManager() {
}
