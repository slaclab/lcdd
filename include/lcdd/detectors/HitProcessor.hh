#ifndef LCDD_DETECTORS_HITPROCESSOR_HH_
#define LCDD_DETECTORS_HITPROCESSOR_HH_ 1

// Geant4
#include "G4Step.hh"

#include "lcdd/detectors/SensitiveDetector.hh"

#include <string>

class SensitiveDetector;

/**
 * @brief Virtual class defining an interface for processing hits from within sensitive detectors.
 */
class HitProcessor {

protected:

    /**
     * Class constructor.
     */
    HitProcessor()
        : _detector(NULL),
          _collectionName(""),
          _collectionIndex(0) {
    }

public:

    /**
     * Class destructor.
     */
    virtual ~HitProcessor() {
    }

    /**
     * Process steps to produce hits.
     * @param[in] step A G4Step object.
     * @return True if hits were created or modified; false if not.
     */
    virtual bool processHits(G4Step* step) = 0;

    /**
     * Get the SensitiveDetector associated with this HitProcessor.
     * @return The SensitiveDetector of this HitProcessor.
     */
    SensitiveDetector* getSensitiveDetector() const {
        return _detector;
    }

    /**
     * Set the SensitiveDetector associated with this HitProcessor.
     * @param[in] detector The SensitiveDetector of this HitProcessor.
     */
    virtual void setSensitiveDetector(SensitiveDetector* detector) {
        _detector = detector;
        if (_collectionName != "") {
            for (int i=0, n=detector->GetNumberOfCollections(); i<n; i++) {
                std::string aCollectionName = detector->GetCollectionName(i);
                if (aCollectionName == _collectionName) {
                    _collectionIndex = i;
                }
            }
        }
    }

    void setCollectionName(const std::string& collectionName) {
        _collectionName = collectionName;
    }

    int getCollectionIndex() {
        return _collectionIndex;
    }

    virtual void reset() {
    }

protected:

    SensitiveDetector* _detector;
    std::string _collectionName;
    int _collectionIndex;
};

#endif
