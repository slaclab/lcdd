#include "lcdd/hits/CalorimeterHit.hh"

// Geant4
#ifdef G4VIS_USE
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Point3D.hh"
#include "G4Transform3D.hh"
#endif

G4Allocator<CalorimeterHit> CalorimeterHitAllocator;

CalorimeterHit::CalorimeterHit() :
        G4VHit(), _edep(0), _endcap(false) {
}

CalorimeterHit::CalorimeterHit(Id64bit id, G4double edep, G4ThreeVector globalCellPos) :
        G4VHit(), _edep(edep), _pos(globalCellPos), _endcap(false), _id(id) {
}

CalorimeterHit::~CalorimeterHit() {
}

CalorimeterHit::CalorimeterHit(const CalorimeterHit &right) :
        G4VHit() {
    _edep = right._edep;
    _pos = right._pos;
    _id = right._id;
    _endcap = right._endcap;
}

const CalorimeterHit& CalorimeterHit::operator=(const CalorimeterHit &right) {
    _edep = right._edep;
    _pos = right._pos;

    return *this;
}

bool CalorimeterHit::operator==(const CalorimeterHit &right) {
    return (_pos == right._pos);
}

#ifdef G4VIS_USE
void CalorimeterHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if(pVVisManager)
    {
        G4Point3D p3D = G4Point3D( _pos );
        G4Circle chit(p3D);
        chit.SetScreenDiameter(3.0);
        chit.SetFillStyle(G4Circle::filled);

        G4Colour col(1.0,0.,1.0);

        chit.SetVisAttributes(G4VisAttributes( col ) );
        pVVisManager->Draw( chit );
    }
}
#endif

void CalorimeterHit::printHitContributions(std::ostream& os) {
    printHitContributionsHeader(os);

    for (HitContributionList::iterator iter = _particleList.begin(); iter != _particleList.end(); iter++) {
        (*iter).printOut(os);
    }
}

void CalorimeterHit::printHitContributionsHeader(std::ostream& os) {
    os << "McpHitContribs" << std::endl;
    os << "trackID" << '\t' << "edep" << '\t' << '\t' << "PdgId" << '\t' << "time" << std::endl;
}

void CalorimeterHit::Print() {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream &os, const CalorimeterHit& hit) {
    os << hit.getPosition() << " " << G4BestUnit(hit.getEdep(), "Energy") << std::endl;
    return os;
}

void CalorimeterHit::setPosition(const G4ThreeVector& posXYZ) {
    _pos = posXYZ;
}

void CalorimeterHit::setEdep(const G4double ed) {
    _edep = ed;
}

void CalorimeterHit::addEdep(const G4double edincr) {
    _edep += edincr;
}

G4ThreeVector CalorimeterHit::getPosition() const {
    return _pos;
}

G4double CalorimeterHit::getEdep() const {
    return _edep;
}

void CalorimeterHit::addHitContribution(HitContribution contrib) {
    _particleList.push_back(contrib);
}

const HitContributionList& CalorimeterHit::getHitContributions() const {
    return _particleList;
}

//void CalorimeterHit::setId64bit(Id64bit::ElementType id0, Id64bit::ElementType id1)
//{
//    _id.setId0(id0);
//    _id.setId1(id1);
//    _id.encode();
//}

const Id64bit& CalorimeterHit::getId64bit() const {
    return _id;
}

void CalorimeterHit::setEndcapFlag(bool ec) {
    _endcap = ec;
}

bool CalorimeterHit::getEndcapFlag() {
    return _endcap;
}
