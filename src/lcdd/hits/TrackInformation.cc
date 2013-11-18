// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/hits/TrackInformation.cc,v 1.4 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/hits/TrackInformation.hh"

G4Allocator<TrackInformation> TrackInformationAllocator;

TrackInformation::TrackInformation() {
    setDefaults();
}

TrackInformation::TrackInformation(const G4Track* aTrack) {
    setDefaults();

    _originalTrackID = aTrack->GetTrackID();
}

TrackInformation::TrackInformation(const TrackInformation* aTrackInfo) {
    assert(aTrackInfo);

    setFromTrackInformation(aTrackInfo, this);
}

TrackInformation::~TrackInformation() {
}

TrackInformation& TrackInformation::operator =(const TrackInformation& right) {
    setFromTrackInformation(&right, this);
    return *this;
}

void TrackInformation::setDefaults() {
    // default to invalid trackID
    _originalTrackID = -1;

    // default to tracking region in both current and orig
    _originalTrackingStatus = TrackInformation::eInTrackingRegion;
    _trackingStatus = TrackInformation::eInTrackingRegion;

    // default flag vals
    _hasTrackerHit = false;
    _vertexIsNotEndpointOfParent = false;
    _backscatter = false;
    _belowThreshold = false;
}

void TrackInformation::setFromTrackInformation(const TrackInformation* srcTrkInfo, TrackInformation* trgtTrkInfo) {
    trgtTrkInfo->setTrackID(srcTrkInfo->_originalTrackID);

    trgtTrkInfo->setOriginalTrackingStatus(srcTrkInfo->_originalTrackingStatus);
    trgtTrkInfo->setTrackingStatus(srcTrkInfo->_trackingStatus);

    trgtTrkInfo->setHasTrackerHit(false);
    trgtTrkInfo->setVertexIsNotEndpointOfParent(false);
    trgtTrkInfo->setBackscatter(srcTrkInfo->getBackscatter());
    trgtTrkInfo->setBelowThreshold(srcTrkInfo->getBelowThreshold());
}

const std::string& TrackInformation::getTrackingStatusString(ETrackingStatus ts) {
    static const std::string str_none = "None";
    static const std::string str_tracking = "InTrackingRegion";
    static const std::string str_nontracking = "InNontrackingRegion";
    static const std::string str_invalid = "Invalid";

    if (ts == eNone) {
        return str_none;
    } else if (ts == eInTrackingRegion) {
        return str_tracking;
    } else if (ts == eInNontrackingRegion) {
        return str_nontracking;
    }

    return str_invalid;
}

int TrackInformation::operator ==(const TrackInformation& right) const {
    return (this == &right);
}

void TrackInformation::Print() const {
}

const std::string& TrackInformation::getTrackingStatusString() const {
    return TrackInformation::getTrackingStatusString(getTrackingStatus());
}

G4int TrackInformation::getOriginalTrackID() const {
    return _originalTrackID;
}

TrackInformation::ETrackingStatus TrackInformation::getOriginalTrackingStatus() const {
    return _originalTrackingStatus;
}

TrackInformation::ETrackingStatus TrackInformation::getTrackingStatus() const {
    return _trackingStatus;
}

bool TrackInformation::hasTrackerHit() const {
    return _hasTrackerHit;
}

void TrackInformation::setHasTrackerHit(bool hasHit) {
    _hasTrackerHit = hasHit;
}

void TrackInformation::setTrackID(G4int id) {
    _originalTrackID = id;
}

void TrackInformation::setTrackingStatus(ETrackingStatus st) {
    _trackingStatus = st;
}

void TrackInformation::setOriginalTrackingStatus(ETrackingStatus st) {
    _originalTrackingStatus = st;
}

void TrackInformation::setVertexIsNotEndpointOfParent(bool val) {
    _vertexIsNotEndpointOfParent = val;
}

bool TrackInformation::getVertexIsNotEndpointOfParent() const {
    return _vertexIsNotEndpointOfParent;
}

void TrackInformation::setBackscatter(bool val) {
    _backscatter = val;
}

bool TrackInformation::getBackscatter() const {
    return _backscatter;
}

void TrackInformation::setBelowThreshold(bool val) {
    _belowThreshold = val;
}

bool TrackInformation::getBelowThreshold() const {
    return _belowThreshold;
}

TrackInformation* TrackInformation::getTrackInformation(const G4Track* aTrack) {
    return static_cast<TrackInformation*>(aTrack->GetUserInformation());
}

TrackInformation* TrackInformation::getTrackInformation(const G4Step* aStep) {
    return getTrackInformation(aStep->GetTrack());
}
