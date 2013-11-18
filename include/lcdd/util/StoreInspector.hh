// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/util/StoreInspector.hh,v 1.9 2013-11-14 00:47:23 jeremy Exp $

#ifndef LCDD_UTIL_STOREINSPECTOR_HH
#define LCDD_UTIL_STOREINSPECTOR_HH 1

// LCDD
#include "lcdd/core/LCDDProcessor.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/geant4/PhysicsLimitSet.hh"
#include "lcdd/geant4/UserRegionInformation.hh"

// Geant4
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"
#include "G4MaterialTable.hh"
#include "G4VSolid.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
#include "G4VUserRegionInformation.hh"
#include "G4VisAttributes.hh"
#include "G4MagneticField.hh"

// STL
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <cassert>
#include <cmath>

using std::endl;

/**
 * @brief Templated class for printing the contents of a Geant4 or LCDD object store using a G4UIcommand.
 * @note
 * The store must have an STL vector or map as its backing data structure.
 */
template<class Object, class ObjectContainer>
class StoreInspector: public G4UImessenger {
public:

    typedef typename ObjectContainer::iterator iterator;
    typedef typename ObjectContainer::const_iterator const_iterator;

public:

    /**
     * Class constructor.
     */
    StoreInspector(const std::string& name, const ObjectContainer* container) :
            G4UImessenger() {
        //assert(container != 0);
        _name = name;
        _container = container;
        defineCommands();
    }

    /**
     * Find an object by name in the list.
     * @param[in] name   The name of the object.
     * @param[in] objVec The list of objects.
     * @return The object with name or 0 if doesn't exist.
     */
    Object* findByName(const std::string& name, const std::vector<Object*>* objVec) {
        Object* obj = 0;
        for (typename std::vector<Object*>::const_iterator it = objVec->begin(); it != objVec->end(); it++) {
            if (sameName(*it, name)) {
                obj = (*it);
                break;
            }
        }
        return obj;
    }

    /*
     * Find an object by name in a map.
     * @param[in] name   The name of the object.
     * @param[in] objMap The object map.
     * @return The object with name or 0 if doesn't exist.
     */
    Object* findByName(const std::string& name, const std::map<std::string, Object*>* objMap) {
        std::map<std::string, Object*>* objMap_nconst = const_cast<std::map<std::string, Object*>*>(objMap);
        return (*objMap_nconst)[name];
    }

    /**
     * Compare an object name.
     * @param[in] obj  The object.
     * @param[in] name The name to compare.
     * @return True if names are the same; false if not.
     */
    bool sameName(Object* obj, const std::string& name) {
        return (((std::string) obj->GetName()) == name);
    }

    /**
     * Find an object by name.
     * @param[in] name The object name.
     * @return The object with name or 0 if doesn't exist.
     */
    Object* find(const std::string& name) {
        return findByName(name, const_cast<const ObjectContainer*>(_container));
    }

    /**
     * Get an object from a map iterator.
     * @param[in] it The map iterator.
     * @return The object from the iterator.
     */
    Object* getObject(typename std::map<std::string, Object*>::const_iterator it) {
        return it->second;
    }

    /**
     * Get an object from a vector iterator.
     * @param[in] it The vector iterator.
     * @return The object from the iterator.
     */
    Object* getObject(typename std::vector<Object*>::const_iterator it) {
        return (*it);
    }

    /**
     * Get the name of the object from a map iterator.
     * @param[in] it The map iterator.
     * @return The name of the object from the iterator.
     */
    const std::string& getObjectName(typename std::map<std::string, Object*>::const_iterator it) {
        return it->first;
    }

    /**
     * Get the name of an object from a vector iterator.
     * @param[in] it The vector iterator.
     * @return The object name.
     */
    const std::string& getObjectName(typename std::vector<Object*>::const_iterator it) {
        return (*it)->GetName();
    }

    /**
     * Print the objects in the store to an output stream.
     * @param[in] os An output stream.
     * @return The same output stream.
     */
    std::ostream& printStore(std::ostream& os) {
        os << "********* " + _name + " store ********" << endl << endl;
        for (const_iterator it = _container->begin(); it != _container->end(); it++) {
            printObject(os, getObjectName(it), getObject(it));
            os << "-------------------------------------" << endl;
        }
        os << "*************************************" << endl << endl;
        return os;
    }

    /**
     * Print a single object's name and data using the stream operator.
     * @param[in] os     An output stream.
     * @param[in] name   The name of the object.
     * @param[in] object The object to print.
     */
    std::ostream& printObject(std::ostream& os, const std::string& name, Object* obj) {
        os << _name << " - " << name << endl;
        os << (*obj) << endl;
        return os;
    }

    /**
     * Define commands to be used with this inspector.
     */
    void defineCommands() {
        _dir = new G4UIdirectory(std::string("/stores/" + _name + "/").c_str());
        _dir->SetGuidance(std::string("Commands for inspecting the " + _name + " store.").c_str());

        _printCmd = new G4UIcmdWithAString(std::string("/stores/" + _name + "/print").c_str(), this);
        _printCmd->SetGuidance(std::string("Print single " + _name + " object or the entire store.").c_str());
        _printCmd->SetParameterName("name", true);
        _printCmd->SetDefaultValue("");
        _printCmd->AvailableForStates(G4State_Idle);
    }

    /**
     * Execute Geant4 UI command on this inspector using its messenger.
     * @param[in] cmd     The UI command.
     * @param[in] newVals The command arguments.
     */
    virtual void SetNewValue(G4UIcommand* cmd, G4String newVals) {
        std::string name = (std::string) newVals;
        if (name != std::string("")) {
            Object* obj = find(name);
            if (obj != 0) {
                printObject(std::cout, name, obj);
            } else {
                std::cerr << "ERROR: Object named " + name + " was not found in the " + _name + " store!" << endl;
            }
        } else {
            printStore(std::cout);
        }
    }

private:
    std::string _name;
    const ObjectContainer* _container;
    G4UIcmdWithAString* _printCmd;
    G4UIdirectory* _dir;
};

/**
 * Following are declarations of specific types of object store inspectors:
 */
typedef StoreInspector<G4Material, G4MaterialTable> G4MaterialStoreInspector;
typedef StoreInspector<G4VSolid, G4SolidStore> G4SolidStoreInspector;
typedef StoreInspector<PhysicsLimitSet, LCDDProcessor::LimitSets> G4LimitSetInspector;
typedef StoreInspector<G4LogicalVolume, G4LogicalVolumeStore> G4LogicalVolumeStoreInspector;
typedef StoreInspector<G4VPhysicalVolume, G4PhysicalVolumeStore> G4PhysicalVolumeStoreInspector;
typedef StoreInspector<IdSpec, IdManager::IdSpecs> IdSpecInspector;
typedef StoreInspector<G4VisAttributes, LCDDProcessor::VisAttributes> G4VisAttributeInspector;
G4VisAttributeInspector visInspector("G4VisAttributes", LCDDProcessor::instance()->getVisAttributesStore());
typedef StoreInspector<G4Region, G4RegionStore> G4RegionStoreInspector;
typedef StoreInspector<SensitiveDetector, LCDDProcessor::SensitiveDetectors> G4SensitiveDetectorInspector;
typedef StoreInspector<G4MagneticField, LCDDProcessor::MagneticFields> G4MagneticFieldInspector;

/**
 * Overloaded print operator for PhysicsLimitSet.
 * @param[in] os     An output stream.
 * @param[in] limset The PhysicsLimitSet to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream& os, PhysicsLimitSet& limset) {
    os << endl;
    for (PhysicsLimitSet::LimitSetMap::const_iterator it = limset.getLimitSetMap().begin(); it != limset.getLimitSetMap().end(); it++) {

        const PhysicsLimitSet::LimitNameType& name = it->first;
        os << name << endl;

        std::string unit = "";
        if (name == "ekin_min") {
            unit = "Energy";
        } else if (name == "range_min") {
            unit = "Length";
        } else if (name == "step_length_max") {
            unit = "Length";
        } else if (name == "time_max") {
            unit = "Time";
        } else if (name == "track_length_max") {
            unit = "Length";
        }

        if (unit != "") {
            const PhysicsLimitSet::LimitMap& limmap = it->second;
            for (PhysicsLimitSet::LimitMap::const_iterator iit = limmap.begin(); iit != limmap.end(); iit++) {

                os << '\t' << iit->first << '\t' << G4BestUnit(iit->second, unit) << endl;
            }
        } else {
            os << "Unknown limit type " << name << endl;
        }
    }
    return os;
}

/**
 * Overloaded stream operator for G4LogicalVolume.
 * @param[in] os An output stream.
 * @param[in] lv The volume to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream &os, G4LogicalVolume &lv) {
    os << "solid: " << lv.GetSolid()->GetName() << endl;
    os << "material: " << lv.GetMaterial()->GetName() << endl;
    os << "mass: " << G4BestUnit(lv.GetMass(), "Mass") << endl;
    os << "daughters: " << lv.GetNoDaughters() << endl;

    G4UserLimits* lim = lv.GetUserLimits();
    os << "limits: ";
    if (0 != lim) {
        os << lim->GetType();
    } else {
        os << "NONE";
    }
    os << endl;

    G4VSensitiveDetector* sd = lv.GetSensitiveDetector();
    os << "SD: ";
    if (0 != sd) {
        os << sd->GetName();
    } else {
        os << "NONE";
    }
    os << endl;

    G4Region* reg = lv.GetRegion();
    os << "region: ";
    if (0 != reg) {
        os << reg->GetName();
    } else {
        os << "NONE";
    }
    os << endl;

    const G4VisAttributes* vis = lv.GetVisAttributes();
    os << "visattributes: ";
    if (0 != vis) {
        os << "yes";
    } else {
        os << "NONE";
    }
    os << endl;

    return os;
}

/**
 * Overloaded print stream operator for G4VPhysicalVolume class.
 * @param[in] os An output stream.
 * @param[in] pv The volume to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream &os, G4VPhysicalVolume &pv) {
    os << "lvolume: " << pv.GetLogicalVolume()->GetName() << endl;
    os << "pos: " << pv.GetTranslation() << endl;
    const G4RotationMatrix* rot = pv.GetRotation();
    os << "rot: ";
    if (0 != rot) {
        rot->print(os);
    } else {
        os << "NONE" << endl;
    }
    os << "copyNo: " << pv.GetCopyNo() << endl;
    os << "# copies: " << pv.GetMultiplicity() << endl;
    return os;
}
/**
 * Overloaded print stream operator for IdSpec class.
 * @param[in] os An output stream.
 * @param[in] id The IdSpec to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream& os, IdSpec& id) {
    os << "# fields: " << id.getNumFields() << endl;
    os << endl;
    os << "label\tstart\tlength\tsigned" << endl;
    for (IdSpec::IdFields::const_iterator it = id.IdFieldsBegin(); it != id.IdFieldsEnd(); it++) {
        IdField* field = *it;
        os << field->getLabel() << '\t' << field->getStart() << '\t' << field->getLength() << '\t' << field->getSigned() << endl;
    }
    return os;
}

/**
 * Overloaded print stream operator for SensitiveDetector class.
 * @param[in] os An output stream.
 * @param[in] sd The SensitiveDetector to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream& os, SensitiveDetector& sd) {
    os << "fullPath: " << sd.GetFullPathName() << endl;
    os << "HC: " << sd.getHCName() << endl;
    os << "HCID: " << sd.getHCID() << endl;
    os << "verbose: " << sd.getVerbose() << endl;
    os << "ecut: " << sd.getEnergyCut() << endl;
    os << "hasIdSpec: " << sd.hasIdSpec() << endl;
    os << "isEndcap: " << sd.getEndcapFlag() << endl;
    os << "isActive: " << sd.isActive() << endl;
    return os;
}

/**
 * Overloaded print stream operator for G4Region class.
 * @param[in] os  An output stream.
 * @param[in] reg The region to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream &os, G4Region &reg) {
    os << "prod cut: " << reg.GetProductionCuts()->GetProductionCut(0) << endl;
    UserRegionInformation* regInfo = static_cast<UserRegionInformation*>(reg.GetUserInformation());
    if (0 != regInfo) {
        os << "store secondaries: " << regInfo->getStoreSecondaries() << endl;
        os << "energy threshold: " << regInfo->getThreshold() << endl;
    } else {
        os << "NO G4UserRegionInformation" << endl;
    }
    return os;
}

/**
 * Overloaded print stream operator for G4MagneticField class.
 * @param[in] os An output stream.
 * @param[in] f  The field to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream& os, G4MagneticField& f) {
    /* Generic B-fields have no displayable data attributes! */
    return os;
}

/**
 * Overloaded print stream operator for G4VisAttribute objects.
 * @param[in] os  An output stream.
 * @param[in] vis The G4VisAttributes to print.
 * @return The same output stream.
 */
std::ostream& operator<<(std::ostream& os, G4VisAttributes &vis) {
    const G4Color& color = vis.GetColor();
    os << "RGB: " << color.GetRed() << " " << color.GetGreen() << " " << color.GetBlue() << endl;
    os << "Alpha: " << color.GetAlpha() << endl;
    os << "visible: " << vis.IsVisible() << endl;
    os << "show daughters: " << !vis.IsDaughtersInvisible() << endl;

    os << "forced drawing style: ";
    if (vis.IsForceDrawingStyle()) {
        G4VisAttributes::ForcedDrawingStyle force = vis.GetForcedDrawingStyle();
        if (force == G4VisAttributes::wireframe) {
            os << "wireframe";
        } else if (force == G4VisAttributes::solid) {
            os << "solid";
        }
    } else {
        os << "NONE";
    }
    os << endl;

    return os;
}

#endif
