/*
 * DDSegmentationCalorimeterHitProcessor.cc
 *
 *  Created on: Aug 8, 2014
 *      Author: jeremym
 */

#include "lcdd/detectors/DDSegmentationCalorimeterHitProcessor.hh"

// LCDD
#include "lcdd/detectors/CurrentTrackState.hh"
#include "lcdd/hits/CalorimeterHitMap.hh"
#include "lcdd/id/IdFactory.hh"

// DD4hep
#include "DDSegmentation/Segmentation.h"

// Geant4
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"

#include <math.h>

//#define DDSegmentationCalorimeterHitProcessor_DEBUG

DDSegmentationCalorimeterHitProcessor::DDSegmentationCalorimeterHitProcessor() {
}

DDSegmentationCalorimeterHitProcessor::~DDSegmentationCalorimeterHitProcessor() {
}

bool DDSegmentationCalorimeterHitProcessor::processHits(G4Step* step) {

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "DDSegmentationCalorimeterHitProcessor::processHits" << G4endl;
#endif

    // Get the energy deposition.
    G4double edep = step->GetTotalEnergyDeposit();
#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  edep: " << edep << G4endl;
#endif

    // Check for Geantino particle type.
    G4ParticleDefinition* def = step->GetTrack()->GetDefinition();
    bool isGeantino = false;
    if (def == G4Geantino::Definition() || def == G4ChargedGeantino::Definition()) {
        isGeantino = true;
    }

    // Get touchable from the PreStepPoint.
    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  stepLen: " << step->GetStepLength() << G4endl;
    G4cout << "  lvol: " << touchable->GetVolume()->GetLogicalVolume()->GetName() << G4endl;
    G4cout << "  mat: " << touchable->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName() << G4endl;
#endif

    // Cut on energy deposition <= cut but allow Geantinos.
    if (edep <= _calorimeter->getEnergyCut() && isGeantino == false) {
#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  cut on low energy: " << edep << G4endl;
#endif
        return false;
    }

    // Get the Segmentation object.
    DD4hep::DDSegmentation::Segmentation* segmentation = _calorimeter->getDDSegmentation();

    if (segmentation == NULL)
        G4Exception("", "", FatalException, "A DDSegmentation object was not set on the calorimeter!");

    // Compute the global midpoint of the step using the pre and post step points.
    G4ThreeVector globalMidVec = (0.5 * (step->GetPreStepPoint()->GetPosition() + step->GetPostStepPoint()->GetPosition()));

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  globalMidVec: " << globalMidVec.x() << " " << globalMidVec.y() << " " << globalMidVec.z() << G4endl;
#endif

    // Create the global position for input to the Segmentation.
    DD4hep::DDSegmentation::Vector3D globalPosition = DD4hep::DDSegmentation::Vector3D(globalMidVec.x(), globalMidVec.y(), globalMidVec.z());

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  globalPosition: " << globalPosition.x() << " " << globalPosition.y() << " " << globalPosition.z() << G4endl;
#endif

    // Compute the local step position for input to the Segmentation.
    G4ThreeVector localVec = touchable->GetHistory()->GetTopTransform().TransformPoint(globalMidVec);

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  localVec: " << localVec.x() << " " << localVec.y() << " " << localVec.z() << G4endl;
#endif

    DD4hep::DDSegmentation::Vector3D localPosition = DD4hep::DDSegmentation::Vector3D(localVec.x(), localVec.y(), localVec.z());
    //DD4hep::DDSegmentation::Vector3D localPosition = DD4hep::DDSegmentation::Vector3D(localVec.x(), localVec.y(), 0);

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  localPosition: " << localPosition.x() << " " << localPosition.y() << " " << localPosition.z() << G4endl;
#endif

    // Create the VolumeID which does not have Segmentation bin values.
    DD4hep::DDSegmentation::VolumeID volumeId = IdFactory::createVolumeId(step, _calorimeter->getIdSpec());

    // Create the encoded 64-bit cell ID from the Segmentation.
    DD4hep::DDSegmentation::CellID cellId = segmentation->cellID(localPosition, globalPosition, volumeId);

    // Check for an existing hit with this identifier.
    CalorimeterHit* hit = _calorimeter->getCalorimeterHitMap(getCollectionIndex())->get(cellId);

    // Was there a hit found with this identifier?
    if (hit == NULL) {

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  creating a new hit " << G4endl;
        G4cout << "  cellID: " << std::hex << cellId << G4endl;
        G4cout << "  fieldDescription: " << segmentation->decoder()->fieldDescription() << G4endl;
        int size = segmentation->decoder()->size();
        G4cout << "  size: " << size << G4endl;
        for (int i=0; i<size; i++) {
            G4cout << "  value[" << i << "] = " << std::dec << (*segmentation->decoder())[i] << G4endl;
        }
#endif

        int id0 = segmentation->decoder()->lowWord();
        int id1 = segmentation->decoder()->highWord();

        Id64bit id = Id64bit(id0, id1);

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  id0: " << std::hex << id0 << G4endl;
        G4cout << "  id1: " << std::hex << id1 << G4endl;
#endif

        // Get the global cell position from the Segmentation.
        DD4hep::DDSegmentation::Vector3D localCellPosition = segmentation->position(cellId);

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  localCellPosition: "
                << std::dec
                << localCellPosition.x() << " "
                << localCellPosition.y() << " "
                << localCellPosition.z() << G4endl;
#endif

        // Create  a G4ThreeVector for the hit's local cell position.
        G4ThreeVector localCellVec = G4ThreeVector(localCellPosition.x(), localCellPosition.y(), localCellPosition.z());

        // Compute the global cell position from the local.
        G4ThreeVector globalCellVec = touchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(localCellVec);

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  globalCellPosition: "
                << std::dec
                << globalCellVec.x() << ", "
                << globalCellVec.y() << ", "
                << globalCellVec.z() << G4endl;
#endif

        // No hit was found, so a new one is created.
        hit = new CalorimeterHit(id, edep, globalCellVec);

        // Add the new hit to the calorimeter.
        _calorimeter->addHit(hit, _collectionIndex);

    } else {

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
        G4cout << "  adding " << std::dec << edep << " to existing hit" << G4endl;
#endif

        // Add energy deposition to an existing hit.
        hit->addEdep(edep);
    }

    // Add hit contribution to the hit.
    // FIXME: This should pass a pointer to a new object.  It is copied, which is inefficient.
    hit->addHitContribution(HitContribution(CurrentTrackState::getCurrentTrackID(), step));

#ifdef DDSegmentationCalorimeterHitProcessor_DEBUG
    G4cout << "  done!" << G4endl;
#endif

    // Return true, indicating that a hit was added or modified.
    return true;
}
