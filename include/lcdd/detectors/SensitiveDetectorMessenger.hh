// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/SensitiveDetectorMessenger.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_SENSITIVEDETECTORMESSENGER_HH
#define LCDD_DETECTORS_SENSITIVEDETECTORMESSENGER_HH 1

// Geant4
#include "G4UImessenger.hh"

// LCDD
#include "SensitiveDetector.hh"

// Geant4
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

/**
 * @brief Geant4 messenger providing macro command interface to SensitiveDetector objects.
 */
class SensitiveDetectorMessenger: public G4UImessenger {

public:

    /**
     * Class constructor.
     * @param[in] detector The SensitiveDetector to connect to the messenger.
     */
    SensitiveDetectorMessenger(SensitiveDetector* detector);

    /**
     * Class destructor.
     */
    virtual ~SensitiveDetectorMessenger();

public:

    /**
     * Execute a messenger command.
     * @param[in] cmd     The messenger command.
     * @param[in] newVals The command arguments.
     */
    virtual void SetNewValue(G4UIcommand* cmd, G4String newVals);

    /**
     * Create the directory for this detector.
     */
    static void makeDetectorsDir();

private:

    /**
     * Define this messenger's commands.
     * @param[in] The SensitiveDetector of this messenger.
     */
    void defineCommands(G4VSensitiveDetector* sd);

private:

    SensitiveDetector* _detector;

    static G4UIdirectory* _detectorsDir;
    G4UIdirectory* _detectorDir;
    G4UIcommand* _printInfoCmd;
    G4UIcommand* _printVolumesCmd;
    G4UIcmdWithAnInteger* _verboseCmd;
    G4UIcmdWithABool* _activateCmd;
    G4UIcmdWithADoubleAndUnit* _ecutCmd;
};

#endif
