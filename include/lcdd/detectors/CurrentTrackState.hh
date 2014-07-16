/*
 * CurrentTrackState.hh
 *
 *  Created on: Jun 24, 2014
 *      Author: jeremym
 */

#ifndef LCDD_DETECTORS_CURRENTTRACKSTATE_HH_
#define LCDD_DETECTORS_CURRENTTRACKSTATE_HH_ 1

// Geant4
#include "globals.hh"

class CurrentTrackState {

private:

	CurrentTrackState() {
	}

public:

	static void setCurrentTrackID(G4int trackID) {
		//G4cout << "setCurrentTrackID - " << trackID << G4endl;
		_currentTrackID = trackID;
	}

	static void setCurrentPrimaryID(G4int trackID) {
		_currentPrimaryID = trackID;
	}

	static G4int getCurrentTrackID() {
		return _currentTrackID;
	}

	static G4int getCurrentPrimaryID() {
		return _currentPrimaryID;
	}

public:

	static G4int _currentTrackID;
	static G4int _currentPrimaryID;
};

#endif /* CURRENTTRACKSTATE_HH_ */
