#include "lcdd/detectors/SensitiveDetectorMessenger.hh"

// Geant4
#include "G4UIcommand.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4VSensitiveDetector.hh"

G4UIdirectory* SensitiveDetectorMessenger::_detectorsDir = 0;

SensitiveDetectorMessenger::SensitiveDetectorMessenger(SensitiveDetector* detector) :
        _detector(detector) {
    if (_detectorsDir == 0) {
        makeDetectorsDir();
    }

    defineCommands(_detector);
}

SensitiveDetectorMessenger::~SensitiveDetectorMessenger() {
    // TODO: Delete command objects here.
}

void SensitiveDetectorMessenger::SetNewValue(G4UIcommand* cmd, G4String newVals) {
    if (cmd == _printInfoCmd) {
        _detector->printBasicInfo(std::cout);
    } else if (cmd == _printVolumesCmd) {
        _detector->printVolumes(std::cout);
    } else if (cmd == _verboseCmd) {
        _detector->setVerbose(_verboseCmd->GetNewIntValue(newVals));
    } else if (cmd == _activateCmd) {
        _detector->Activate(_activateCmd->GetNewBoolValue(newVals));
    } else if (cmd == _ecutCmd) {
        _detector->setEcut(_ecutCmd->GetNewDoubleValue(newVals));
    }

}

void SensitiveDetectorMessenger::makeDetectorsDir() {
    _detectorsDir = new G4UIdirectory("/detectors/");
    _detectorsDir->SetGuidance("Commands for sensitive detectors. [LCDD]");
}

void SensitiveDetectorMessenger::defineCommands(G4VSensitiveDetector* sd) {
    // Name of the sensitive detector.
    const G4String& name = sd->GetName();

    // Name of the sensitive detector's command directory.
    const G4String& dirName = G4String("/lcdd/detectors/" + name + "/");

    // Create the sensitive detector's Geant4 macro command directory.
    _detectorDir = new G4UIdirectory(dirName.c_str());
    _detectorDir->SetGuidance(G4String("Commands for the sensitive detector " + name).c_str());

    // Print command.
    _printInfoCmd = new G4UIcommand(G4String(dirName + "print").c_str(), this);
    _printInfoCmd->SetGuidance(G4String("Print basic information about the sensitive detector " + name).c_str());

    // Print energy deposition.
    _printVolumesCmd = new G4UIcommand(G4String(dirName + "printVolumes").c_str(), this);
    _printVolumesCmd->SetGuidance(G4String("Print a list of logical volume names associated with the detector " + name).c_str());

    // Set the verbosity.
    _verboseCmd = new G4UIcmdWithAnInteger(G4String(dirName + "setVerbose").c_str(), this);
    _verboseCmd->SetGuidance(G4String("Set the verbosity of the detector " + name).c_str());
    _verboseCmd->SetDefaultValue(2);
    _verboseCmd->SetParameterName("verbose", true, true);

    // Activate or deactive this detector.
    _activateCmd = new G4UIcmdWithABool(G4String(dirName + "setActive").c_str(), this);
    _activateCmd->SetGuidance(G4String("Set whether the detector " + name + " is active.").c_str());
    _activateCmd->SetDefaultValue(true);
    _activateCmd->SetParameterName("active", true, true);

    // Set the ecut with unit.
    _ecutCmd = new G4UIcmdWithADoubleAndUnit(G4String(dirName + "setHitEnergyCut").c_str(), this);
    _ecutCmd->SetGuidance(G4String("Set the single hit energy cut for detector " + name).c_str());
    _ecutCmd->SetDefaultValue(0.0);
    _ecutCmd->SetDefaultUnit("GeV");
    _ecutCmd->SetParameterName("cut", true, true);
}
