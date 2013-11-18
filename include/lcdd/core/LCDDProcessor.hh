// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/core/LCDDProcessor.hh,v 1.7 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_CORE_LCDDPROCESSOR_HH
#define LCDD_CORE_LCDDPROCESSOR_HH 1

// Geant4
#include "G4MagneticField.hh"
#include "G4Region.hh"
#include "G4VisAttributes.hh"

// LCDD
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/geant4/PhysicsLimitSet.hh"
#include "lcdd/geant4/LCDDHeaderRecord.hh"

#include <string>
#include <map>

class G4Run;

/**
 * @brief Registers LCDD objects as they are created, generally from XML subscribers.
 * @note  This is the LCDD equivalent of the GDMLProcessor class.
 */
class LCDDProcessor {

private:

    /**
     * Class constructor, which is private because class is accessed via singleton.
     */
    LCDDProcessor();

public:

    /**
     * Class destructor.
     */
    virtual ~LCDDProcessor();

    /**
     * Get the static instance of this class.
     * @return The singleton instance of this class.
     */
    static LCDDProcessor* instance();

public:

    /** Name to SensitiveDetector map. */
    typedef std::map<std::string, SensitiveDetector*> SensitiveDetectors;

    /** Name to magnetic field map. */
    typedef std::map<std::string, G4MagneticField*> MagneticFields;

    /** Name to regions map. */
    typedef std::map<std::string, G4Region*> Regions;

    /** Name to vis attributes map. */
    typedef std::map<std::string, G4VisAttributes*> VisAttributes;

    /** Name to physics limit map. */
    typedef std::map<std::string, PhysicsLimitSet*> LimitSets;

public:

    /**
     * Get the header record.
     * @return The LCDD header record.
     */
    const LCDDHeaderRecord* getHeader() const;

    /**
     * Set the header record.
     * @param[in] h The header record.
     */
    void setHeader(LCDDHeaderRecord* h);

    /**
     * Get the name of the detector.
     */
    std::string getDetectorName() const;

    /**
     * Add a named SensitiveDetector.
     * @param[in] name The name of the detector.
     * @param[in] sd   The sensitive detector.
     */
    void addSensitiveDetector(std::string& name, SensitiveDetector* sd);

    /**
     * Get a SensitiveDetector by name.
     * @param[in] The name of the detector.
     */
    SensitiveDetector* getSensitiveDetector(const std::string& name);

    /**
     * Get a SensitiveDetector by name.
     * @param[in] The name of the detector.
     */
    SensitiveDetector* getSensitiveDetector(const char* name);

    /**
     * Get an iterator pointing at the beginning of the SD map.
     * @return An iterator pointing at the first SD in the map.
     */
    LCDDProcessor::SensitiveDetectors::const_iterator getSensitiveDetectorsBegin();

    /**
     * Get an iterator pointing at the end of the SD map.
     * @return An iterator pointing to the end of the SD map.
     */
    LCDDProcessor::SensitiveDetectors::const_iterator getSensitiveDetectorsEnd();

    /**
     * Add a magnetic field by name.
     * @param[in] name The name of the magnetic field.
     * @param[in] mag  The magnetic field object.
     */
    void addMagneticField(std::string& name, G4MagneticField* mag);

    /**
     * Get a magnetic field by name.
     * @param[in] name The name of the magnetic field.
     */
    G4MagneticField* getMagneticField(const std::string& name);

    /**
     * Get a magnetic field by name.
     * @param[in] name The name of the magnetic field.
     */
    G4MagneticField* getMagneticField(const char* name);

    /**
     * Get an iterator pointing at the first magnetic field in the map.
     * @return An iterator pointing at the first magnetic field in the map.
     */
    LCDDProcessor::MagneticFields::const_iterator getMagneticFieldsBegin();

    /**
     * Get an iterator pointing at the end of the magnetic field map.
     * @return An iterator pointing at the end of the magnetic field map.
     */
    LCDDProcessor::MagneticFields::const_iterator getMagneticFieldsEnd();

    /**
     * Add a global magnetic field.
     * @param[in] mag The magnetic field to add.
     */
    void addGlobalField(G4MagneticField* mag);

    /**
     * Add a region by name.
     * @param[in] name The name of the region.
     * @param[in] reg  The region to add.
     */
    void addRegion(std::string& name, G4Region* reg);

    /**
     * Get a region by name.
     * @param[in] name The name of the region.
     * @return The region.
     */
    G4Region* getRegion(const std::string& name);

    /**
     * Get a region by name.
     * @param[in] name The name of the region.
     * @return The region.
     */
    G4Region* getRegion(const char* name);

    /**
     * Get an iterator pointing to the first region in the map.
     * @return An iterator pointing to the first region in the map.
     */
    LCDDProcessor::Regions::const_iterator getRegionsBegin();

    /**
     * Get an iterator pointing to the end of the region map.
     * @return An iterator pointing to the end of the region map.
     */
    LCDDProcessor::Regions::const_iterator getRegionsEnd();

    /**
     * Add a PhysicsLimitSet by name.
     * @param[in] name The name of the physics limit set.
     * @param[in] lim  The PhysicsLimitSet object to register.
     */
    void addLimitSet(std::string& name, PhysicsLimitSet* lim);

    /**
     * Get a PhysicsLimitSet by name.
     * @param[in] name The name of the PhysicsLimitSet object.
     * @return The matching PhysicsLimitSet object.
     */
    PhysicsLimitSet* getLimitSet(const std::string& name);

    /**
     * Get a PhysicsLimitSet by name.
     * @param[in] name The name of the PhysicsLimitSet object.
     * @return The matching PhysicsLimitSet object.
     */
    PhysicsLimitSet* getLimitSet(const char* name);

    /**
     * Get an iterator pointing to the first PhysicsLimitSet in the map.
     * @return An iterator pointing to the first PhysicsLimitSet in the map.
     */
    LCDDProcessor::LimitSets::const_iterator getLimitSetsBegin();

    /**
     * Get an iterator pointing to the end of the PhysicsLimitSet map.
     * @return An iterator pointing to the end of the PhysicsLimitSet.
     */
    LCDDProcessor::LimitSets::const_iterator getLimitSetsEnd();

    /**
     * Add VisAttributes by name.
     * @param[in] name The name of the VisAttributes to add.
     * @param[in] vis  The VisAttributes object to add.
     */
    void addVisAttributes(std::string& name, G4VisAttributes* vis);

    /**
     * Get VisAttributes by name.
     * @param[in] The name of the VisAttributes.
     */
    G4VisAttributes* getVisAttributes(const std::string& name);

    /**
     * Get VisAttributes by name.
     * @param[in] The name of the VisAttributes.
     */
    G4VisAttributes* getVisAttributes(const char* name);

    /**
     * Get an iterator pointing to the first VisAttributes in the map.
     * @return An iterator pointing to the first VisAttributes in the map.
     */
    LCDDProcessor::VisAttributes::const_iterator getVisAttributesBegin();

    /**
     * Get an iterator pointing to the end of the VisAttributes map.
     * @return An iterator pointing to the end of the VisAttributes map.
     */
    LCDDProcessor::VisAttributes::const_iterator getVisAttributesEnd();

    /**
     * Get the map of VisAttributes.
     * @return The map of VisAttributes.
     */
    const LCDDProcessor::VisAttributes* getVisAttributesStore() const;

    /**
     * Get the map of SDs.
     * @return The map of SDs.
     */
    const LCDDProcessor::SensitiveDetectors* getSensitiveDetectorStore() const;

    /**
     * Get the map of magnetic fields.
     * @return The map of magnetic fields.
     */
    const LCDDProcessor::MagneticFields* getMagneticFieldStore() const;

    /**
     * Get the map of regions.
     * @return The map of regions.
     */
    const LCDDProcessor::Regions* getRegionStore() const;

    /**
     * Get the map of PhysicsLimitSets.
     * @return The map of PhysicsLimitSets.
     */
    const LCDDProcessor::LimitSets* getLimitSetStore() const;

private:

    // header info for the lcdd file
    LCDDHeaderRecord* _header;

    // vectors of SD, mag, regions, visAttributes
    LCDDProcessor::SensitiveDetectors _sensitiveDetectors;
    LCDDProcessor::MagneticFields _magneticFields;
    LCDDProcessor::Regions _regions;
    LCDDProcessor::VisAttributes _visAttributes;
    LCDDProcessor::LimitSets _limitSets;

    // static singleton instance var
    static LCDDProcessor* _instance;
};

#endif
