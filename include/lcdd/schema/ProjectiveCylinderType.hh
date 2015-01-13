/*
 * ProjectiveCylinderType.hh
 *
 *  Created on: Aug 12, 2014
 *      Author: jeremym
 */

#ifndef LCDD_SCHEMA_PROJECTIVECYLINDERTYPE_HH_
#define LCDD_SCHEMA_PROJECTIVECYLINDERTYPE_HH_ 1

#include "lcdd/schema/SegmentationType.hh"

class ProjectiveCylinderType : public SegmentationType {

public:

    void set_theta_bins(const std::string theta_bins) {
        _theta_bins = theta_bins;
    }

    const std::string& get_theta_bins() {
        return _theta_bins;
    }

    void set_phi_bins(const std::string phi_bins) {
        _phi_bins = phi_bins;
    }

    const std::string& get_phi_bins() {
        return _phi_bins;
    }

    void set_offset_theta(const std::string offset_theta) {
        _offset_theta = offset_theta;
    }

    const std::string& get_offset_theta() {
        return _offset_theta;
    }

    void set_offset_phi(const std::string offset_phi) {
        _offset_phi = offset_phi;
    }

    const std::string& get_offset_phi() {
        return _offset_phi;
    }

private:

    std::string _theta_bins;
    std::string _phi_bins;
    std::string _offset_theta;
    std::string _offset_phi;
};

#endif /* LCDD_SCHEMA_PROJECTIVECYLINDERTYPE_HH_ */
