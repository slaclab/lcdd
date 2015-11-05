#ifndef LCDD_DETECTORS_CURRENTTRACKSTATE_HH_
#define LCDD_DETECTORS_CURRENTTRACKSTATE_HH_ 1

// Geant4
#include "globals.hh"

/**
 * @brief
 * A global static track ID to be set externally from LCDD
 */
class CurrentTrackState {

private:

	CurrentTrackState() {
	}

public:

	static void setCurrentTrackID(G4int trackID) {
		_currentTrackID = trackID;
	}

	static G4int getCurrentTrackID() {
		return _currentTrackID;
	}

public:

	static G4int _currentTrackID;
	//static G4int _currentPrimaryID;
};

#endif
