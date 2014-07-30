#ifndef LCDD_UTIL_GDMLWRITERMESSENGER_HH_
#define LCDD_UTIL_GDMLWRITERMESSENGER_HH_ 1

// Geant4
#include "G4UImessenger.hh"

class G4UIcommand;

/**
 * @brief The Geant4 messenger class for the GDMLWriter.
 */
class GDMLWriterMessenger: public G4UImessenger {

public:

    /**
     * Class constructor.
     */
    GDMLWriterMessenger();

    /**
     * Class destructor.
     */
    virtual ~GDMLWriterMessenger();

public:

    /**
     * Execute UI command.
     * @param[in] cmd     The command to execute.
     * @param[in] newVals The command arguments.
     */
    void SetNewValue(G4UIcommand* cmd, G4String newVals);

private:

    /**
     * Define the messenger commands.
     */
    void defineCommands();

private:

    G4UIcommand* _dumpGDMLCmd;
};
// class
#endif
