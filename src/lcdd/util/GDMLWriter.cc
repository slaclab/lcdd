// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/util/GDMLWriter.cc,v 1.2 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/util/GDMLWriter.hh"

// GDML
#include "G4Writer/G4GDMLWriter.h"

// Geant4
#include "G4VPhysicalVolume.hh"
#include "G4TransportationManager.hh"

void GDMLWriter::writeCurrentGeometry(const std::string& fileName, std::vector<std::string> volumes) {
    G4VPhysicalVolume* world = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();
    G4GDMLWriter g4writer("http://www.lcsim.org/schemas/gdml/1.0/gdml.xsd", fileName);
    try {
        g4writer.DumpGeometryInfo(world, volumes);
    } catch (std::exception &err) {
        G4cerr << "problem writing geometry: " << err.what() << std::endl;
    }
}

void GDMLWriter::writeCurrentGeometry(const std::string& fileName) {
    G4cout << "Dumping current geometry to file <" << fileName << ">" << G4endl;

    G4VPhysicalVolume* world =
    G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();

    G4GDMLWriter g4writer("http://www.lcsim.org/schemas/gdml/1.0/gdml.xsd", fileName);

    try {
        g4writer.DumpGeometryInfo(world);
    }
    catch(std::exception &lerr) {
        G4cerr << "problem writing geometry: " << lerr.what () << std::endl;
    }
}
