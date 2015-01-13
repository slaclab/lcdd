#include "lcdd/id/IdFactory.hh"

// Uncomment to enable verbose debug output from this class.
//#define ID_DEBUG 1

// LCDD
#include "lcdd/detectors/CalorimeterSD.hh"
#include "lcdd/detectors/ReadoutUtil.hh"
#include "lcdd/id/IdManager.hh"
#include "lcdd/segmentation/Segmentation.hh"



// Geant4
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NavigationHistory.hh"

using namespace std;

IdFactory::Bits const IdFactory::MASK_ON = 0xFFFFFFFF;

Id64bit IdFactory::createIdentifier(const IdVec& idVec, IdSpec* idSpec) {
    /*
     #ifdef ID_DEBUG
     G4cout << G4endl;
     G4cout.setf( ios::hex );
     G4cout << "IdFactory::createId64bit()" << G4endl;
     G4cout << "idvec size: " << idVec.size() << G4endl;
     G4cout << "idspec numFields: " << idSpec->getNumFields() << G4endl;
     G4cout << "idspec bitLength: " << idSpec->getBitLength() << G4endl;
     #endif
     */

    /* IdVec (expanded id) size must equal IdSpec size or die. */
    if (idVec.size() != idSpec->getNumFields()) {
        G4Exception("", "", FatalException, "idspec size != idvec size.");
    }

    /* A 2 member array for cell ids 1 & 2 (2x32-bit int). */
    Bits values[2] = { 0, 0 };
    size_t valueIndex = 0;

    /* Ptr to value of current idx. */
    Bits* valueP = &values[valueIndex];

    /* Ptr to the current idfield. */
    IdField* field = 0;

    /* Flag indicating that next 32-bit id has been reached. */
    bool nextId = false;

    /* loop vars */
    IdField::SizeType fieldLength = 0;
    Bits curr_bit = 0;
    IdSpec::SizeType idspec_idx = 0;

    /* Loop over the IdVec, packing its values into the 64-bit Id using information from the IdSpec. */
    for (IdVec::ElementVector::const_iterator iter = idVec.getFieldsBegin(); iter != idVec.getFieldsEnd(); iter++) {

        /* field ptr from idspec */
        field = idSpec->getIdField(idspec_idx);
        assert(field);

        /* id value of field */
        Id64bit::ElementType field_val = (Id64bit::ElementType) *iter;

        /* field length */
        fieldLength = field->getLength();

        /* field start */
        Bits fieldStart = field->getStart();

        /* Don't allow crossing of 32-bit boundary.
         FIXME: See http://jira.slac.stanford.edu/browse/LCDD-21
         */
        if ((fieldStart < 32) && (fieldStart + fieldLength > 32)) {
            G4cerr << "Field <" << field->getLabel() << "> crosses the 32-bit boundary." << G4endl;
            G4Exception("", "", FatalException, "Fields are not allowed to cross the 32-bit boundary.");
            /* Check if on 2nd int. */
        } else if (fieldStart >= 32) {

            /* If 1st time, set id val pntr. */
            if (!nextId) {
#ifdef ID_DEBUG
                G4cout << "setting ptr to next id" << G4endl;
#endif
                ++valueIndex;
                valueP = &values[valueIndex];
                nextId = true;
            }

            /* Adjust start idx for position in next 32-bit id. */
            fieldStart -= 32;
        }

        Bits mask = makeBitMask(fieldLength);

        /*
         #ifdef ID_DEBUG
         G4cout << "idspec_idx: " << dec << idspec_idx << G4endl;
         G4cout << "shifting left: " << dec << fieldLength << G4endl;
         G4cout << "curr_bit: " << dec << curr_bit << G4endl;
         G4cout << "field_label: " << field->getLabel() << G4endl;
         G4cout << "field_start: " << fieldStart << G4endl;
         G4cout << "field_val (dec): " << dec << field_val << G4endl;
         G4cout << "field_val (hex): " << hex << field_val << G4endl;
         G4cout << "field_bit_len: " << dec << fieldLength << G4endl;
         G4cout << "field_mask: " << hex << mask << G4endl;
         #endif
         */

        /* For positive values, check that this value doesn't overflow the assigned length. */
        //    if ( field_val > 0 ) {
        if (checkOverflow(field_val, mask) != 0) {
            G4cerr << "Value <" << field_val << "> is too big for the field <" << field->getLabel() << ">, len <" << fieldLength << ">." << G4endl;
            G4Exception("", "", FatalException, "Value too large for field.");
        }
        //    }
        //    else {
        //    }

        /*
         #ifdef ID_DEBUG
         G4cout << "field_mask: " << hex << mask << G4endl;
         #endif
         */

        /* Apply bit mask and shift to proper left pos. */
        Bits field_val_shifted_masked = (field_val & mask) << fieldStart;

        /* AND into the current id val. */
        (*valueP) = (*valueP) | field_val_shifted_masked;

        /* Set current bit to next start pos. */
        curr_bit += field->getLength();

#ifdef ID_DEBUG
        G4cout << "id64_val (hex): " << hex << *valueP << G4endl;
        G4cout << G4endl;
#endif

        /* Increment the idspec idx. */
        ++idspec_idx;
    }

#ifdef ID_DEBUG
    G4cout << "end curr_bit: " << dec << curr_bit << G4endl;
    G4cout << "end id64[0]: " << hex << values[0] << G4endl;
    G4cout << "end id64[1]: " << hex << values[1] << G4endl;
    G4cout.unsetf( ios::hex );
    G4cout << G4endl << G4endl;
#endif

    /* Make a 64-bit id to return. */
    Id64bit id(values[0], values[1]);

    // DEBUG
    //size_t oldWidth = cout.width();
    //std::cout.width(8);
    //std::cout << "created Id64bit: " << hex << id.getValue() << std::endl;
    //std::cout << "  id0: " << hex << id.getId0() << std::endl;
    //std::cout << "  id1: " << hex << id.getId1() << std::endl;
    //std::cout.width(oldWidth);

    return id;
}

inline IdFactory::Bits IdFactory::makeBitMask(IdField::SizeType len) {
    return (Bits) ((1 << len) - 1);
}

inline IdFactory::Bits IdFactory::checkOverflow(Id64bit::ElementType val, Bits mask) {
    Bits xbits = 0x0;

    /* get flipped mask of all 1's in positions that should be masked off for this val */
    Bits flipMask = mask ^ MASK_ON;

    /* mask off all the valid bits, leaving overflow bits */
    Id64bit::ElementType overflow = (val & flipMask);

    /* for pos vals, check that no bits past max bit are = 1 */
    if (val >= 0) {
        xbits = (Bits) ((flipMask) & overflow);
    }
    /* for neg vals, check that no bits past max bit are = 0 */
    else {
        xbits = (Bits) ((flipMask) ^ overflow);
    }

#ifdef ID_DEBUG
    G4cout << "flipMask: " << hex << flipMask << G4endl;
    G4cout << "overflow: " << hex << overflow << G4endl;
    G4cout << "overflow bits (hex): " << hex << xbits << G4endl;
#endif

    return xbits;
}

IdVec IdFactory::createOrderedIdVec(G4Step* aStep, const SensitiveDetector* sd) {
    //std::cout << "createOrderedIdVec" << std::endl;

    assert(aStep);
    assert(sd);

    IdSpec* idspec = sd->getIdSpec();
    IdVec ids;

    Segmentation* seg = 0;
    if (sd->getType() == SensitiveDetector::eCalorimeter) {
        seg = (dynamic_cast<const CalorimeterSD*>(sd))->getSegmentation();
    }

    if (idspec) {
        for (IdSpec::IdFields::const_iterator iter = idspec->IdFieldsBegin(); iter != idspec->IdFieldsEnd(); iter++) {

            IdField* f = *iter;

            int bin_val = 0;
            bool fnd_it = false;

#ifdef ID_DEBUG
            G4cout << "handling field: " << f->getLabel() << G4endl;
#endif

            // look in seg, if exists
            if (seg) {
                int bin_idx = IdFactory::findFieldIdxInSegmentation(seg, f->getLabel());

                if (bin_idx != -1) {
                    //std::cout << "getting bin: " << bin_idx << std::endl;
                    bin_val = seg->getBin(bin_idx);
                    //std::cout << "got bin val: " << bin_val << std::endl;
                    fnd_it = true;
                }
#ifdef ID_DEBUG
                else {
                    G4cout << "not in segmentation" << G4endl;
                }
#endif
            }

            // find in PV ids
            if (!fnd_it) {
                std::vector<G4VPhysicalVolume*> pv_list = ReadoutUtil::getPhysVolList(aStep);

                if (hasPhysVolId(pv_list, f->getLabel())) {
                    fnd_it = true;
                    bin_val = findIdInPhysVols(pv_list, f->getLabel());
                }
#ifdef ID_DEBUG
                else {
                    G4cout << "not in physvolids" << G4endl;
                }
#endif

            }

            /* Find in copy numbers of the volume. */
            if (!fnd_it && f->getLabel() == "volume") {
                bin_val = ReadoutUtil::getVolumeNumber(aStep->GetPreStepPoint()->GetTouchableHandle());

                if (-1 == bin_val) {
                    G4Exception("", "", FatalException, "Valid copy number not found for PV.");
                } else {
                    fnd_it = true;
                }
            }
#ifdef ID_DEBUG
            else {
                G4cout << "not in volume (copyNum)" << G4endl;
            }
#endif

            // Push back zero as the default value for field not found.
            ids.addFieldValue(bin_val);

#ifdef ID_DEBUG
            G4cout << "set bin val: " << bin_val << G4endl << G4endl;
#endif
        }
    }

    return ids;
}

int IdFactory::findFieldIdxInSegmentation(Segmentation* seg, const std::string& field_name) {
    const std::vector<std::string>& bin_names = seg->getBinNames();

    int bin_count = 0;
    bool fnd = false;
    for (std::vector<std::string>::const_iterator iter = bin_names.begin(); iter != bin_names.end(); iter++) {
        if (*iter == field_name) {
            fnd = true;
            break;
        }
        ++bin_count;
    }

    if (!fnd) {
        bin_count = -1;
    }

    return bin_count;
}

int IdFactory::findIdInPhysVols(const std::vector<G4VPhysicalVolume*>& pvs, const std::string& field_name) {
    IdManager* id_mgr = IdManager::instance();

#ifdef ID_DEBUG
    G4cout << "looking for field_name match on <" << field_name << ">" << G4endl;
#endif

    int id = 0;
    G4VPhysicalVolume* pv = 0;
    bool fnd = false;

    for (std::vector<G4VPhysicalVolume*>::const_iterator iter_pv = pvs.begin(); iter_pv != pvs.end(); iter_pv++) {
        pv = *iter_pv;

#ifdef ID_DEBUG
        G4cout << "searching in ids of PV <" << pv->GetName() << ">" << G4endl;
#endif

        if (id_mgr->hasPhysVolIds(pv)) {
            PhysVolId::PhysVolIds pvids = id_mgr->getPhysVolIds(pv);
            for (PhysVolId::PhysVolIds::const_iterator iter = pvids.begin(); iter != pvids.end(); iter++) {

#ifdef ID_DEBUG
                G4cout << "current field <" << (*iter).getFieldName() << ">" << G4endl;
#endif

                if ((*iter).getFieldName() == field_name) {
#ifdef ID_DEBUG
                    G4cout << "found a match" << G4endl;
#endif
                    id = (*iter).getValue();
                    fnd = true;
                    break;
                }
#ifdef ID_DEBUG
                else {
                    G4cout << "no match on this PV" << G4endl;
                }
#endif
            }
        }

        if (fnd) {
            break;
        }
    }

    return id;
}

bool IdFactory::hasPhysVolId(const std::vector<G4VPhysicalVolume*>& pvs, const std::string& field_name) {
    IdManager* id_mgr = IdManager::instance();

    G4VPhysicalVolume* pv = 0;
    bool fnd = false;

    for (std::vector<G4VPhysicalVolume*>::const_iterator iter_pv = pvs.begin(); iter_pv != pvs.end(); iter_pv++) {
        pv = *iter_pv;

        if (id_mgr->hasPhysVolIds(pv)) {
            PhysVolId::PhysVolIds pvids = id_mgr->getPhysVolIds(pv);
            for (PhysVolId::PhysVolIds::const_iterator iter = pvids.begin(); iter != pvids.end(); iter++) {

                if ((*iter).getFieldName() == field_name) {
                    fnd = true;
                    break;
                }
            }
        }

        if (fnd) {
            break;
        }
    }

    return fnd;
}

DD4hep::DDSegmentation::VolumeID IdFactory::createVolumeId(G4Step* aStep, IdSpec* idspec) {
    IdVec idvec;
    for (IdSpec::IdFields::const_iterator iter = idspec->IdFieldsBegin(); iter != idspec->IdFieldsEnd(); iter++) {
        IdField* field = *iter;
        std::vector<G4VPhysicalVolume*> pvolumes = ReadoutUtil::getPhysVolList(aStep);
        if (hasPhysVolId(pvolumes, field->getLabel())) {
            int pvolId = findIdInPhysVols(pvolumes, field->getLabel());
            idvec.addFieldValue(pvolId);
        } else {
            idvec.addFieldValue(0);
        }
    }
    Id64bit id = IdFactory::createIdentifier(idvec, idspec);
    id.encode();
    Id64bit::ValueType volId = id.getValue();
    return (DD4hep::DDSegmentation::VolumeID)volId;
}
