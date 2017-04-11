#include "Saxana/SAXComponentFactory.h"

#include <iostream>

extern "C" {

/**
 * Function for loading LCDD SAX processes.
 */
void LCDDLoadProcesses() {

    // Header
    LOAD_COMPONENT (headerProcess);
    LOAD_COMPONENT (detectorProcess);
    LOAD_COMPONENT (authorProcess);
    LOAD_COMPONENT (generatorProcess);
    LOAD_COMPONENT (commentProcess);

    // Volume extended
    LOAD_COMPONENT (volumeExtendedProcess);
    LOAD_COMPONENT (physvolidProcess);

    // Sensitive Detectors
    LOAD_COMPONENT (calorimeterProcess);
    LOAD_COMPONENT (trackerProcess);
    LOAD_COMPONENT (sdrefProcess);

    // Hit Processors
    LOAD_COMPONENT (hit_processorProcess);

    // Segmentations
    LOAD_COMPONENT (grid_xyzProcess);
    LOAD_COMPONENT (projective_cylinderProcess);
    LOAD_COMPONENT (projective_zplaneProcess);
    LOAD_COMPONENT (global_grid_xyProcess);
    LOAD_COMPONENT (cell_readout_2dProcess);

    // Identifiers
    LOAD_COMPONENT (idspecProcess);
    LOAD_COMPONENT (idfieldProcess);
    LOAD_COMPONENT (idspecrefProcess);

    // B-fields
    LOAD_COMPONENT (fieldrefProcess);
    LOAD_COMPONENT (global_fieldProcess);
    LOAD_COMPONENT (solenoidProcess);
    LOAD_COMPONENT (rz_field_mapProcess);
    LOAD_COMPONENT (rzbProcess);
    LOAD_COMPONENT (dipoleProcess);
    LOAD_COMPONENT (dipole_coeffProcess);
    LOAD_COMPONENT (box_dipoleProcess);
    LOAD_COMPONENT (field_map_3dProcess)

    // Region
    LOAD_COMPONENT (regionProcess);
    LOAD_COMPONENT (regionrefProcess);

    // Visualization
    LOAD_COMPONENT (visProcess);
    LOAD_COMPONENT (visrefProcess);
    LOAD_COMPONENT (colorProcess);

    // Physics limits
    LOAD_COMPONENT (limitsetProcess);
    LOAD_COMPONENT (limitsetrefProcess);
    LOAD_COMPONENT (limitProcess);
}

/**
 * Function for loading LCDD subscribers to create runtime objects.
 */
void LCDDLoadSubscribers() {
    // Header
    LOAD_COMPONENT (headerSubscriber);

    // Sensitive Detectors
    LOAD_COMPONENT (calorimeterSubscriber);
    LOAD_COMPONENT (trackerSubscriber);

    // Identifiers
    LOAD_COMPONENT (idspecSubscriber);

    // B-fields
    LOAD_COMPONENT (solenoidSubscriber);
    LOAD_COMPONENT (rz_field_mapSubscriber);
    LOAD_COMPONENT (dipoleSubscriber);
    LOAD_COMPONENT (box_dipoleSubscriber);
    LOAD_COMPONENT (global_fieldSubscriber);
    LOAD_COMPONENT (field_map_3dSubscriber);

    // Regions
    LOAD_COMPONENT (regionSubscriber);

    // Visualization
    LOAD_COMPONENT (visSubscriber);

    // Physics limits
    LOAD_COMPONENT (limitsetSubscriber);
}

/**
 * Function for loading LCDD processes and subscribers.
 */
void LCDDLibLoad() {
    LCDDLoadProcesses();
    LCDDLoadSubscribers();
}
}
