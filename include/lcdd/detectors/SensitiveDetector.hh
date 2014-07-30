#ifndef LCDD_DETECTORS_SENSITIVEDETECTOR_HH_
#define LCDD_DETECTORS_SENSITIVEDETECTOR_HH_ 1

// Geant4
#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"

// LCDD
#include "lcdd/detectors/StepReadout.hh"
#include "lcdd/detectors/HitProcessor.hh"
#include "lcdd/id/IdSpec.hh"
#include "lcdd/id/Id64bit.hh"

class G4UImessenger;
class G4VHitsCollection;

/**
 * @brief A basic implementation of G4VSensitiveDetector.
 * @note  Primary attributes include verbosity, energy cut,
 *        IdSpec,and hits collections.
 */
class SensitiveDetector: public G4VSensitiveDetector, protected StepReadout {
public:

    /**
     * EType indicates the basic type of detector, e.g. tracker or calorimeter.
     */
    enum EType {
        eNone = 0, eTracker = 1, eCalorimeter = 2
    };

    static const std::string& TRACKER;
    static const std::string& CALORIMETER;
    static const std::string& UNKNOWN;

    typedef std::vector<HitProcessor*> HitProcessors;

public:

    /**
     * Class constructor.
     * @param[in] sdName The name of the detector.
     * @param[in] hcName The name of the hit collection.
     * @param[in] sdType The type of the detector.
     */
    SensitiveDetector(G4String sdName, G4String hcName, EType sdType);

    /**
     * Class constructor.
     * @param[in] sdName  The name of the detector.
     * @param[in] hcNames The names of the hit collections.
     * @param[in] sdType  The type of the detector.
     */
    SensitiveDetector(G4String sdName, const std::vector<G4String>& hcNames, EType sdType);

    /**
     * Class destructor.
     */
    virtual ~SensitiveDetector();

    /**
     * Geant4 initialization function called at beginning of event.
     * @param[in] hce The hit collections of this event.
     */
    virtual void Initialize(G4HCofThisEvent* hce);

    /**
     * Geant4 EndOfEvent hook.
     * @param[in] hce The hit collections of this event.
     */
    virtual void EndOfEvent(G4HCofThisEvent* hce);

    /**
     * Get the type of this detector encoded as an enum.
     * @return The type of this detector as an enum.
     */
    SensitiveDetector::EType getType() const;

    /**
     * Get the type of this detector encoded as a string.
     */
    const std::string& getTypeString() const;

    /**
     * Get the hit collection ID associated with this detector.
     * @return The hit collection ID.
     */
    G4int getHCID() const;

    /**
     * Get the hit collection ID from the index.
     * @param[in] nHC The hit collection index.
     * @return The hit collection ID.
     */
    G4int getHCID(G4int nHC) const;

    /**
     * Check whether the G4LogicalVolume can be readout by this detector.
     * Base function just checks that the volume is not null.
     * @param[in] lv The G4LogicalVolume object.
     * @return True if volume is valid; false if not.
     */
    virtual bool isValidVolume(G4LogicalVolume* lv);

    /**
     * Get the hit collection name associated with this detector.
     * @return The name of the hit collection.
     */
    const std::string& getHCName() const;

    /**
     * Get the hit collection by index.
     * @return The hit collection by index.
     */
    const std::string& getHCName(G4int nHC) const;

    /**
     * Set the verbosity level of this detector.
     * @param[in] v The verbosity level.
     */
    void setVerbose(unsigned int v);

    /**
     * Get the verbosity level of this detector.
     * @return The verbosity level of this detector.
     */
    unsigned int getVerbose() const;

    /**
     * Get the hit energy cut of this detector (GeV).
     * @return The energy cut.
     */
    G4double getEnergyCut();

    /**
     * Set the hit energy cut of this detector.
     * @param[in] ecut The energy cut.
     */
    void setEcut(G4double ecut);

    /**
     * Set the identifier specification for this detector.
     * @param[in] idspec The identifier specification.
     */
    void setIdSpec(IdSpec* idspec);

    /**
     * Get the identifier specification for this detector.
     * @return The identifier specification.
     */
    IdSpec* getIdSpec() const;

    /**
     * Check whether this detector has an associated identifier specification.
     * @return True if detector has identifier specification; false if not.
     */
    bool hasIdSpec() const;

    /**
     * Set the endcap flag.
     * @param[in] ec Set the endcap flag.
     */
    void setEndcapFlag(bool ec = true);

    /**
     * Get the endcap flag.
     * @return The flag indicating endcap or not.
     */
    bool getEndcapFlag();

    /**
     * Print basic information about this detector.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    virtual std::ostream& printBasicInfo(std::ostream& os);

    /**
     * Print the names of volumes associated to this detector.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    virtual std::ostream& printVolumes(std::ostream& os);

    /**
     * Get the number of hits collections associated to this detector.
     * @return The number of hit collections.
     */
    int getNumberOfHitsCollections() const;

    /**
     * Get a list of G4LogicalVolume objects that have been assigned to this detector.
     * @return The list of G4LogicalVolume objects assigned to this detector.
     */
    std::vector<G4LogicalVolume*> getLogicalVolumes() const;

    /**
     * Add a hit processor.
     * @param[in] processor The hit processor.
     */
    void addHitProcessor(HitProcessor* processor);

    /**
     * Add a list of hit processors.
     * @param processors The list of hit processors.
     */
    void addHitProcessors(HitProcessors processors);

    /**
     * Create a 64-bit identifier based on the step information.
     * @param[in] step A G4Step object.
     * @return A 64-bit identifier generated from the step information.
     */
    Id64bit makeIdentifier(G4Step* step) const;

    /**
     * Get the list of HitProcessors.
     * @return The list of HitProcessors.
     */
    HitProcessors getHitProcessors();

protected:

    /**
     * Geant4 function to make hits from the step.
     * @param[in] step      The G4Step object.
     * @param[in] touchable The touchable handle to the current geometry.
     */
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* touchable);

    /**
     * Get the (first) hit collection associated with this detector.
     * @return The hit collection associated with this detector.
     */
    G4VHitsCollection* getHitsCollection() const;

    /**
     * Get a hits collection, using the hits collection ID (HCID).
     * @return The hit collection from the HC ID.
     */
    G4VHitsCollection* getHitsCollection(G4int) const;

    /**
     * Set the Hits Collection ID.
     * @param[in] The hit collection ID.
     */
    void setHCID(G4int hcid);

    /**
     * Set the Hits Collection ID for a given collection.
     * @param[in] hcid The hit collection ID.
     * @param[in] nHC  The numerical index of the hit collection.
     */
    void setHCID(G4int hcid, G4int nHC);

protected:

    // vector containing Hit Collection ID's
    std::vector<G4int> _hcids;

    // verbosity
    unsigned int _verbose;

    // endcap flag for LCIO's CHBIT_BARREL bit
    bool _endcap;

    // energy cut
    double _ecut;

    // identifier field description
    IdSpec* _idspec;

private:

    // detector type
    EType _type;

    // The Geant4 command messenger associated with this detector.
    G4UImessenger* _messenger;

    // List of hit processors to be called for each step.
    HitProcessors _hitProcessors;
};

#endif
