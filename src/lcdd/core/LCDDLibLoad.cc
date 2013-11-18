#include "Saxana/SAXComponentFactory.h"

#include <iostream>

extern "C" {

/**
 * Function for loading LCDD SAX processes.
 */
void LCDDLoadProcesses() {

    // header
    LOAD_COMPONENT (headerProcess);
    LOAD_COMPONENT (detectorProcess);
    LOAD_COMPONENT (authorProcess);
    LOAD_COMPONENT (generatorProcess);
    LOAD_COMPONENT (commentProcess);

    // volume extended
    LOAD_COMPONENT (volumeExtendedProcess);
    LOAD_COMPONENT (physvolidProcess);

    // SDs
    LOAD_COMPONENT (calorimeterProcess);
    LOAD_COMPONENT (trackerProcess);
    LOAD_COMPONENT (sdrefProcess);

    // hit_processor
    LOAD_COMPONENT (hit_processorProcess);
    LOAD_COMPONENT (hits_collectionProcess);

    // segmentations
    LOAD_COMPONENT (grid_xyzProcess);
    LOAD_COMPONENT (projective_cylinderProcess);
    LOAD_COMPONENT (projective_zplaneProcess);
    LOAD_COMPONENT (nonprojective_cylinderProcess);
    LOAD_COMPONENT (global_grid_xyProcess);
    LOAD_COMPONENT (cell_readout_2dProcess);

    // Ids
    LOAD_COMPONENT (idspecProcess);
    LOAD_COMPONENT (idfieldProcess);
    LOAD_COMPONENT (idspecrefProcess);

    // field
    LOAD_COMPONENT (fieldrefProcess);
    LOAD_COMPONENT (global_fieldProcess);
    LOAD_COMPONENT (solenoidProcess);
    LOAD_COMPONENT (rz_field_mapProcess);
    LOAD_COMPONENT (rzbProcess);
    LOAD_COMPONENT (dipoleProcess);
    LOAD_COMPONENT (dipole_coeffProcess);
    LOAD_COMPONENT (box_dipoleProcess);
    LOAD_COMPONENT (field_map_3dProcess)

    // region
    LOAD_COMPONENT (regionProcess);
    LOAD_COMPONENT (regionrefProcess);

    // display
    LOAD_COMPONENT (visProcess);
    LOAD_COMPONENT (visrefProcess);
    LOAD_COMPONENT (colorProcess);

    // limit
    LOAD_COMPONENT (limitsetProcess);
    LOAD_COMPONENT (limitsetrefProcess);
    LOAD_COMPONENT (limitProcess);
}

/**
 * Function for loading LCDD subscribers.
 */
void LCDDLoadSubscribers() {
    // subscribers
    LOAD_COMPONENT (headerSubscriber);

    // volume extended
    //LOAD_COMPONENT(volumeExtendedSubscriber);

    // SDs
    LOAD_COMPONENT (calorimeterSubscriber);
    LOAD_COMPONENT (trackerSubscriber);

    // Ids
    LOAD_COMPONENT (idspecSubscriber);

    // field
    LOAD_COMPONENT (solenoidSubscriber);
    LOAD_COMPONENT (rz_field_mapSubscriber);
    LOAD_COMPONENT (dipoleSubscriber);
    LOAD_COMPONENT (box_dipoleSubscriber);
    LOAD_COMPONENT (global_fieldSubscriber);
    LOAD_COMPONENT (field_map_3dSubscriber);

    // region
    LOAD_COMPONENT (regionSubscriber);

    // display
    LOAD_COMPONENT (visSubscriber);

    // limit
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
