// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/detectors/CalorimeterSD.hh,v 1.12 2013-11-14 00:47:19 jeremy Exp $

#ifndef LCDD_DETECTORS_CALORIMETERSD_HH
#define LCDD_DETECTORS_CALORIMETERSD_HH 1

// Geant4
#include "lcdd/detectors/SensitiveDetector.hh"
#include "lcdd/detectors/HitComparator.hh"
#include "lcdd/hits/CalorimeterHit.hh"
#include "lcdd/hits/CalorimeterHitMap.hh"
#include "lcdd/segmentation/Segmentation.hh"

/**
 * @brief The implementation of a calorimeter that accumulates energy depositions by event.
 */
class CalorimeterSD: public SensitiveDetector {

public:

    /**
     * Type definition for a list of LCDD CalorimeterHit objects.
     */
    typedef std::vector<CalorimeterHit*> CalorimeterHitList;

public:

    /**
     * Class constructor.
     * @param[in] sdName   The name of the sensitive detector.
     * @param[in] hcName   The name of the output hit collection.
     * @param[in] sdSeg    The detector's segmentation object for dividing into artificial cells.
     * @param[in] compare  The hit comparator to be used by this detector.
     */
    CalorimeterSD(G4String sdName, G4String hcName, Segmentation* sdSeg);

    /**
     * Class constructor.
     * @param[in] sdName   The name of the sensitive detector.
     * @param[in] hcName   The name of the output hit collections.
     * @param[in] sdSeg    The detector's segmentation object for dividing into artificial cells.
     * @param[in] compare  The hit comparator to be used by this detector.
     */
    CalorimeterSD(G4String sdName, const std::vector<G4String>& hcNames, Segmentation* sdSeg);

    /**
     * Class destructor.
     */
    virtual ~CalorimeterSD();

    /**
     * Check whether a given logical volume is valid for this detector.
     * @return True if lv is valid; false if not.
     */
    bool isValidVolume(G4LogicalVolume* lv);

    /**
     * Implementation of Geant4's G4VSensitiveDetector::Initialize method.
     * @param[in] hc The hit collection of the event.
     */
    void Initialize(G4HCofThisEvent* hc);

    /**
     * Implementation of Geant4's G4VSensitiveDetector::EndOfEvent method.
     * @param[in] hc The hit collection of the event.
     */
    void EndOfEvent(G4HCofThisEvent* hc);

    /**
     * Get the segmentation of this detector or 0 if unset.
     * @return The detector's segmentation.
     */
    Segmentation* getSegmentation() const;

    /**
     * Print out the hit data to an output stream.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    //std::ostream& printHits(std::ostream& os);

    /**
     * Print the calorimeter's basic information.
     * @param[in] os The output stream.
     * @return The same output stream.
     */
    std::ostream& printBasicInfo(std::ostream& os);

    /**
     * Add a hit to one of this Calorimeter's hit collections.
     * @param[in] hit             The hit to add.
     * @param[in] collectionIndex The index of the hit collection.
     * @todo Deprecated => remove.
     */
    void addHit(CalorimeterHit* hit, int collectionIndex = 0);

    /**
     * Find a CalorimeterHit by ID.
     * @param[in] id The Id64bit to lookup.
     * @param[in] collectionIndex The index of the hits collection.
     * @return A hit with matching ID or null if does not exist.
     */
    CalorimeterHit* findHit(const Id64bit& id, int collectionIndex = 0);

protected:

    /**
     * Process step to make hits.
     * @param[in] step      The G4Step of the energy deposition.
     * @param[in] touchable The touchable handle to the geometry.
     */
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* touchable);

protected:

    // The calorimeter's virtual segmentation.
    Segmentation* _segmentation;

    // Pointers to current hits collections.
    std::vector<CalorimeterHitsCollection*> _hitsCollections;

    // A list of hit maps, one per hits collection.
    std::vector<CalorimeterHitMap*> _hitMaps;
};

#endif
