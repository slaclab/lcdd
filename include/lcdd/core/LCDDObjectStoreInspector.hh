#ifndef LCDD_CORE_LCDDOBJECTSTOREINSPECTOR_HH_
#define LCDD_CORE_LCDDOBJECTSTOREINSPECTOR_HH_ 1

// LCDD
#include "lcdd/util/StoreInspector.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/core/LCDDProcessor.hh"

/**
 * @brief Creates specific instances of the StoreInspector for looking at information
 * in Geant4 and LCDD object stores.
 * @bug For some reason moving the code to a source file results in duplicate symbols, so
 * it is left here for now.
 */
class LCDDObjectStoreInspector {

public:

    /**
     * Class constructor.
     * @brief Constructor that defines instances of StoreInspector for specific types.
     */
    LCDDObjectStoreInspector() {
        _materialInspector = new G4MaterialStoreInspector("G4Material", G4Material::GetMaterialTable());
        _solidInspector = new G4SolidStoreInspector("G4VSolid", G4SolidStore::GetInstance());
        _limitsetInspector = new G4LimitSetInspector("G4LimitSet", LCDDProcessor::instance()->getLimitSetStore());
        _lvolumeInspector = new G4LogicalVolumeStoreInspector("G4LogicalVolume", G4LogicalVolumeStore::GetInstance());
        _pvolumeInspector = new G4PhysicalVolumeStoreInspector("G4VPhysicalVolume", G4PhysicalVolumeStore::GetInstance());
        _idspecInspector = new IdSpecInspector("IdSpec", IdManager::instance()->getIdSpecStore());
        _sdInspector = new G4SensitiveDetectorInspector("G4SensitiveDetector", LCDDProcessor::instance()->getSensitiveDetectorStore());
        _regionInspector = new G4RegionStoreInspector("G4Region", G4RegionStore::GetInstance());
        _fieldInspector = new G4MagneticFieldInspector("G4MagneticField", LCDDProcessor::instance()->getMagneticFieldStore());
        _visInspector = new G4VisAttributeInspector("G4VisAttributes", LCDDProcessor::instance()->getVisAttributesStore());
    }

    /**
     * Class destructor.
     */
    virtual ~LCDDObjectStoreInspector() {
        delete _materialInspector;
        delete _solidInspector;
        delete _limitsetInspector;
        delete _lvolumeInspector;
        delete _pvolumeInspector;
        delete _idspecInspector;
        delete _sdInspector;
        delete _regionInspector;
        delete _fieldInspector;
        delete _visInspector;
    }

private:

    G4MaterialStoreInspector* _materialInspector;
    G4SolidStoreInspector* _solidInspector;
    G4LimitSetInspector* _limitsetInspector;
    G4LogicalVolumeStoreInspector* _lvolumeInspector;
    G4PhysicalVolumeStoreInspector* _pvolumeInspector;
    IdSpecInspector* _idspecInspector;
    G4SensitiveDetectorInspector* _sdInspector;
    G4RegionStoreInspector* _regionInspector;
    G4MagneticFieldInspector* _fieldInspector;
    G4VisAttributeInspector* _visInspector;
};

#endif
