/*
 * VUserTrackInformation.hh
 *
 *  Created on: Jun 24, 2014
 *      Author: jeremym
 */
#ifndef LCDD_GEANT4_VUSERTRACKINFORMATION_HH_
#define LCDD_GEANT4_VUSERTRACKINFORMATION_HH_

#include "G4Track.hh"

/**
 * A pure virtual class for track information in LCDD,
 * which allows an external module to define the implementation,
 * e.g. SLIC.
 */
class VUserTrackInformation : public G4VUserTrackInformation {

	/**
	 * Update the track information from a G4Track.
	 * @param The G4Track associated to the track information.
	 */
	//virtual void setTrack(const G4Track* track) = 0;

public:

	virtual void setHasTrackerHit() = 0;
};

#endif /* VUSERTRACKINFORMATION_HH_ */
