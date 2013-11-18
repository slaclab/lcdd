// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/core/GeometryManager.cc,v 1.6 2013-11-13 23:02:56 jeremy Exp $

// LCDD
#include "lcdd/core/GeometryManager.hh"

// LCDD
#include "lcdd/geant4/UserRegionInformation.hh"
//#include "lcdd/core/G4StoreManager.hh"

// GDML
#include "G4Processor/GDMLProcessor.h"

// Geant4
#include "G4Run.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"

GeometryManager* GeometryManager::m_instance = 0;

GeometryManager::GeometryManager() :
        m_worldRegionIsSetup(false) {
}

GeometryManager::~GeometryManager() {
}

GeometryManager* GeometryManager::instance() {
    if (m_instance == 0) {
        m_instance = new GeometryManager();
    }

    return m_instance;
}

void GeometryManager::beginRun(const G4Run*) {
    // only setup world region info on first run
    if (!m_worldRegionIsSetup) {
        setupWorldRegionInformation();
    }
}

G4LogicalVolume* GeometryManager::getWorldLogicalVolume() const {
    //return GDMLProcessor::GetInstance()->GetWorldVolume()->GetLogicalVolume();
    return getWorldPhysicalVolume()->GetLogicalVolume();
}

G4VPhysicalVolume* GeometryManager::getWorldPhysicalVolume() const {
    return G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();
}

void GeometryManager::setupWorldRegionInformation() {
    G4LogicalVolume* worldLV = getWorldLogicalVolume();

    assert(worldLV);

    UserRegionInformation* regInfo = new UserRegionInformation();
    regInfo->setStoreSecondaries(false);
    regInfo->setThreshold(0.0);

    worldLV->GetRegion()->SetUserInformation(regInfo);
    m_worldRegionIsSetup = true;
}

void GeometryManager::checkOverlaps() const {
    checkOverlaps(getWorldLogicalVolume(), true);
}

void GeometryManager::checkOverlaps(G4LogicalVolume* lvolume, bool recurse) const {
    if (lvolume == 0)
        return;

    for (G4int i = 0; i < lvolume->GetNoDaughters(); i++) {

        G4PVPlacement* dau = static_cast<G4PVPlacement*>(lvolume->GetDaughter(i));

        if (dau) {
            // Check overlaps of daughters in mother.
            dau->CheckOverlaps();

            // Recursively check overlaps of daughters.
            if (recurse) {
                checkOverlaps(dau->GetLogicalVolume(), true);
            }
        }
    }
}

void GeometryManager::checkOverlaps(const G4String& name, bool recurse) const {
    G4LogicalVolumeStore* store = G4LogicalVolumeStore::GetInstance();
    bool found = false;
    for (std::vector<G4LogicalVolume*>::iterator it = store->begin(); it != store->end(); it++) {
        G4LogicalVolume* vol = (*it);
        if (vol->GetName() == name) {
            checkOverlaps(vol, recurse);
            found = true;
            break;
        }
    }
    if (!found) {
        G4cerr << "WARNING: The logical volume named <" << name << "> was not found in the G4LogicalVolumeStore!" << std::endl;
    }
}
