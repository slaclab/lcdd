// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/hits/TrackerHit.cc,v 1.7 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/hits/TrackerHit.hh"

// Geant4
#ifdef G4VIS_USE
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Point3D.hh"
#include "G4Transform3D.hh"
#endif

G4Allocator<TrackerHit> G4TrackerHitAllocator;

TrackerHit::TrackerHit() :
        G4VHit(), _edep(0), _tdep(0), _trkID(-1), _length(0) {
}

TrackerHit::~TrackerHit() {
}

#ifdef G4VIS_USE
void TrackerHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if(pVVisManager) {

        G4Point3D p3D = G4Point3D( _pos );
        G4Circle chit(p3D);
        chit.SetScreenDiameter(3.0);
        chit.SetFillStyle(G4Circle::filled);

        G4Colour col(1.0, 0.0, 1.0);

        chit.SetVisAttributes(G4VisAttributes( col ) );
        pVVisManager->Draw( chit );
    }
}
#endif

void TrackerHit::Print() {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream &os, const TrackerHit& hit) {
    std::cout << hit.getTrackID() << " " << hit.getPosition() << " " << G4BestUnit(hit.getEdep(), "Energy") << " " << hit.getMomentum() << " "
            << G4BestUnit(hit.getLength(), "Length") << " " << G4BestUnit(hit.getTdep(), "Time") << " " << hit.getPDG() << " " << std::endl;
    return os;
}

void TrackerHit::setTdep(const G4double tdep) {
    _tdep = tdep;
}

void TrackerHit::setEdep(const G4double edep) {
    _edep = edep;
}

void TrackerHit::setPosition(const G4ThreeVector& posXYZ) {
    _pos = posXYZ;
}

void TrackerHit::setMomentum(const G4ThreeVector& mom) {
    _mom = mom;
}

void TrackerHit::setTrackID(const G4int trkID) {
    _trkID = trkID;
}

void TrackerHit::setPDG(const G4int pdg) {
    _PDG = pdg;
}

void TrackerHit::setLength(const G4double l) {
    _length = l;
}

G4double TrackerHit::getTdep() const {
    return _tdep;
}

G4double TrackerHit::getEdep() const {
    return _edep;
}

G4ThreeVector TrackerHit::getPosition() const {
    return _pos;
}

G4ThreeVector TrackerHit::getMomentum() const {
    return _mom;
}

G4int TrackerHit::getTrackID() const {
    return _trkID;
}

G4int TrackerHit::getPDG() const {
    return _PDG;
}

G4double TrackerHit::getLength() const {
    return _length;
}

void TrackerHit::setId(Id64bit::ElementType id1) {
    _id.setId1(id1);
}

int TrackerHit::getId() {
    return _id.getId1();
}
