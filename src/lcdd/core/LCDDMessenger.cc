#include "lcdd/core/LCDDMessenger.hh"

// LCDD
#include "lcdd/core/LCDDParser.hh"
#include "lcdd/core/GeometryManager.hh"
#include "lcdd/util/NistElementsDump.hh"
#include "lcdd/util/StringUtil.hh"

// Geant4
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"

// STL
#include <cassert>

LCDDMessenger::LCDDMessenger() {
    // define UI commands
    defineCommands();
}

LCDDMessenger::~LCDDMessenger() {
    delete _setupCmd;
    delete _setURICmd;
    delete _setSetupNameCmd;
    delete _setVersionCmd;
    delete _lcddDir;
}

void LCDDMessenger::SetNewValue(G4UIcommand *cmd, G4String newVals) {
    LCDDParser* parser = LCDDParser::instance();

    G4String singleArg = newVals;
    std::istringstream is((const char*) newVals);

    if (cmd == _setURICmd) {
        parser->setURI(singleArg);
    } else if (cmd == _setSetupNameCmd) {
        parser->setSetupName(singleArg);
    } else if (cmd == _setVersionCmd) {
        parser->setVersion(singleArg);
    } else if (cmd == _setupCmd) {
        G4String uri, setup, version;

        is >> uri >> setup >> version;

        parser->setURI(uri);
        parser->setSetupName(setup);
        parser->setVersion(version);
    } else if (cmd == _dumpCmd) {
        //std::cout<<"arg: "<<singleArg<<std::endl;
        NistElementsDump::writeXml(singleArg);
    } else if (cmd == _checkOverlapsCmd || cmd == _checkOverlapsRecurseCmd) {

        bool recurse = false;

        if (cmd == _checkOverlapsRecurseCmd) {
            recurse = true;
        }

        G4String vol("");
        is >> vol;

        G4cout << "vol=" << vol << G4endl;
        G4cout << "recurse=" << recurse << G4endl;

        if (newVals != "") {
            // Check the named volume with optional recursion.
            GeometryManager::instance()->checkOverlaps(vol, recurse);
        } else {
            // No volume.  Check the world, which is always done recursively!
            GeometryManager::instance()->checkOverlaps();
        }
    } else {
        G4cerr << "WARNING: Unknown cmd to LCDDMessenger - " << cmd << G4endl;
    }
}

G4String LCDDMessenger::GetCurrentValue(G4UIcommand *) {
    return G4String("");
}

void LCDDMessenger::defineCommands() {
    G4UIparameter *p;

    // LCDD directory
    _lcddDir = new G4UIdirectory("/lcdd/");
    _lcddDir->SetGuidance("XML detector description and geometry commands. [LCDD]");

    // set URL for input geometry file
    _setURICmd = new G4UIcommand("/lcdd/url", this);
    _setURICmd->SetGuidance("Set the Uniform Resource Locator (URL) for the input geometry file.");
    _setURICmd->AvailableForStates(G4State_PreInit);

    p = new G4UIparameter("URI", 's', false);
    _setURICmd->SetParameter(p);

    // set name of GDML setup
    _setSetupNameCmd = new G4UIcommand("/lcdd/setupName", this);
    _setSetupNameCmd->SetGuidance("Set GDML setup name.");
    _setSetupNameCmd->AvailableForStates(G4State_PreInit);

    p = new G4UIparameter("SetupName", 's', false);
    _setSetupNameCmd->SetParameter(p);

    // set version of GDML setup
    _setVersionCmd = new G4UIcommand("/lcdd/version", this);
    _setVersionCmd->SetGuidance("Set GDML version tag.");
    _setVersionCmd->AvailableForStates(G4State_PreInit);

    p = new G4UIparameter("Version", 's', false);
    _setVersionCmd->SetParameter(p);

    // setup URI, Setup and Version in one command
    _setupCmd = new G4UIcommand("/lcdd/setup", this);
    _setupCmd->SetGuidance("Set URI, SetupName and Version with a single command.");
    _setupCmd->AvailableForStates(G4State_PreInit);

    p = new G4UIparameter("URI", 's', false);
    p->SetGuidance("URI is a URL to the input file.  It MUST NOT contain unescaped spaces.");
    _setupCmd->SetParameter(p);

    p = new G4UIparameter("SetupName", 's', true);
    _setupCmd->SetParameter(p);

    p = new G4UIparameter("Version", 's', true);
    _setupCmd->SetParameter(p);

    _dumpCmd = new G4UIcommand("/lcdd/dumpNistElements", this);
    _dumpCmd->SetGuidance("Dump NIST elements to file as GDML fragment, including lambda and X0.");
    p = new G4UIparameter("Filename", 's', true);
    p->SetDefaultValue("NistElements.xml");
    _dumpCmd->SetParameter(p);

    // Check overlaps.
    _checkOverlapsCmd = new G4UIcommand("/lcdd/checkOverlaps", this);
    _checkOverlapsCmd->SetGuidance("Call CheckOverlaps on a given volume or the world volume (no arguments).");

    p = new G4UIparameter("Volume", 's', true);
    p->SetDefaultValue("");
    _checkOverlapsCmd->SetParameter(p);

    // Check overlaps with recursion to daughters.
    _checkOverlapsRecurseCmd = new G4UIcommand("/lcdd/checkOverlapsRecurse", this);
    _checkOverlapsRecurseCmd->SetGuidance("Call CheckOverlaps on a given volume and recursively check daughters.");

    p = new G4UIparameter("Volume", 's', true);
    p->SetDefaultValue("");
    _checkOverlapsRecurseCmd->SetParameter(p);
}
