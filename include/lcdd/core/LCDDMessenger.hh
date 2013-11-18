// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/core/LCDDMessenger.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_CORE_LCDDMESSENGER_HH
#define LCDD_CORE_LCDDMESSENGER_HH 1

#include "G4UImessenger.hh"

class G4UIcommand;
class G4UIdirectory;

class LCDDDetectorConstruction;

/**
 * @brief G4UImessenger implementation for various LCDD commands.
 * @todo This class should create the "stores" directory also.
 */
class LCDDMessenger: public G4UImessenger {

public:

    /**
     * Class constructor.
     */
    LCDDMessenger();

    /**
     * Class destructor.
     */
    virtual ~LCDDMessenger();

public:

    /**
     * Execute a command on this messner.
     * @param[in] cmd     The command to execute.
     * @param[in] newVals The command's argument values.
     */
    void SetNewValue(G4UIcommand *cmd, G4String newVals);

    /**
     * Get the current value of the messenger.
     * @warning This is not actually implemented and just returns a dummy value.
     */
    G4String GetCurrentValue(G4UIcommand *cmd);

private:

    /**
     * Define the directory and commands for this messenger.
     */
    void defineCommands();

private:

    G4UIdirectory* _lcddDir;
    G4UIcommand* _setupCmd;
    G4UIcommand* _setURICmd;
    G4UIcommand* _setSetupNameCmd;
    G4UIcommand* _setVersionCmd;
    G4UIcommand* _dumpCmd;
    G4UIcommand* _checkOverlapsCmd;
    G4UIcommand* _checkOverlapsRecurseCmd;
};
// class
#endif
