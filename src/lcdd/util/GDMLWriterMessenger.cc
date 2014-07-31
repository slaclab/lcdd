#include "lcdd/util/GDMLWriterMessenger.hh"

// LCDD
#include "lcdd/util/GDMLWriter.hh"

// Geant4
#include "G4UIcmdWithAString.hh"

GDMLWriterMessenger::GDMLWriterMessenger() {
    defineCommands();
}

GDMLWriterMessenger::~GDMLWriterMessenger() {
}

void GDMLWriterMessenger::SetNewValue(G4UIcommand *, G4String newVals) {
    std::string volume;
    std::string fileName;
    std::istringstream is(newVals);

    is >> fileName >> volume;

    if (volume.length() > 1) {
        std::vector<std::string> volumes;
        volumes.push_back(volume);
        GDMLWriter::writeCurrentGeometry(fileName, volumes);
    } else {
        GDMLWriter::writeCurrentGeometry(fileName);
    }
}

void GDMLWriterMessenger::defineCommands() {
    _dumpGDMLCmd = new G4UIcommand("/lcdd/dumpGDML", this);
    _dumpGDMLCmd->SetGuidance("Dump current geometry to GDML output file.");
    G4UIparameter* p = new G4UIparameter("outputFile", 's', false);
    _dumpGDMLCmd->SetParameter(p);
    p = new G4UIparameter("topVolume", 's', true);
    _dumpGDMLCmd->SetParameter(p);
    _dumpGDMLCmd->AvailableForStates(G4State_Idle);
}

