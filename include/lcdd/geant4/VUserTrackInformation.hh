#ifndef LCDD_GEANT4_VUSERTRACKINFORMATION_HH_
#define LCDD_GEANT4_VUSERTRACKINFORMATION_HH_

#include "G4Track.hh"

/**
 * A pure virtual class for track information in LCDD,
 * which allows an external module to define the implementation,
 * e.g. SLIC.
 */
class VUserTrackInformation : public G4VUserTrackInformation {
public:
	virtual void setHasTrackerHit() = 0;
};

#endif
