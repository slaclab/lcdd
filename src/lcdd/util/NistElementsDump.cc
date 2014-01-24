// $Id: NistElementsDump.cc,v 1.3 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/util/NistElementsDump.hh"
#include "lcdd/util/StringUtil.hh"

// GDML
#include "Writer/Element.h"

// Geant4
#include "G4String.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

// STL
#include <vector>
#include <fstream>

using gdml::writer::Element;

using namespace std;

#include "lcdd/util/ElementNames.icc"

NistElementsDump::NistElementsDump() {
}

void NistElementsDump::writeXml(const std::string& filename) {
    ofstream fstr;
    fstr.open(filename.c_str(), fstream::out);
    printXml(fstr);
    fstr.close();
}

void NistElementsDump::printXml(std::ostream& out) {
    // Get the NIST manager from G4.
    G4NistManager* mgr = G4NistManager::Instance();

    // Create the XML root node.
    Element* materials = new Element("materials");

    // Loop over chemical elements array.
    for (int i = 0; i < nelements; i++) {
        // Get the element abbreviation and name.
        const std::string& elemAbbrev = abbrevs[i];
        const std::string& elemName = names[i];

        // Get element and material from G4.
        G4Element* elem = mgr->FindOrBuildElement(elemAbbrev);
        if (elem == 0) {
            std::cout << elemAbbrev << " not found." << std::endl;
            continue;
        }
        const std::string& g4mat = "G4_" + elemAbbrev;
        G4Material* mat = mgr->FindOrBuildMaterial(g4mat);
        if (mat == 0) {
            std::cout << g4mat << " not found." << std::endl;
            continue;
        }

        // Create new element.
        Element* elemNode = new Element("element");
        elemNode->addAttribute("name", elem->GetName());
        elemNode->addAttribute("formula", elem->GetSymbol());
        elemNode->addAttribute("Z", StringUtil::toString(elem->GetZ()));

        // Setup atom.
        Element* atomNode = new Element("atom");
        atomNode->addAttribute("type", "A");
        atomNode->addAttribute("unit", "g/mol");
        atomNode->addAttribute("value", StringUtil::toString((elem->GetA() * mole / g)));

        // Append atom node to element.
        elemNode->appendChild(*atomNode);

        // Append element node to top.
        materials->appendChild(*elemNode);

        // Create material node.
        Element* matNode = new Element("material");
        matNode->addAttribute("name", elemName);
        matNode->addAttribute("formula", elem->GetName());

        // Set material state.
        G4State g4state = mat->GetState();
        std::string state;
        if (g4state == kStateSolid) {
            state = "solid";
        } else if (g4state == kStateLiquid) {
            state = "liquid";
        } else if (g4state == kStateGas) {
            state = "gas";
        } else {
            state = "unknown";
        }
        matNode->addAttribute("state", state);

        // Add radlen node.
        Element* radlNode = new Element("RL");
        radlNode->addAttribute("unit", "cm");
        radlNode->addAttribute("type", "X0");
        radlNode->addAttribute("value", StringUtil::toString(mat->GetRadlen() / cm));
        matNode->appendChild(*radlNode);

        // Add nuclear interaction length node.
        Element* nilNode = new Element("NIL");
        nilNode->addAttribute("unit", "cm");
        nilNode->addAttribute("type", "lambda");
        nilNode->addAttribute("value", StringUtil::toString(mat->GetNuclearInterLength() / cm));
        matNode->appendChild((*nilNode));

        // Add density node.
        Element* densNode = new Element("D");
        densNode->addAttribute("type", "density");
        densNode->addAttribute("unit", "g/cm3");
        double matDens = mat->GetDensity() / (g / cm3);
        densNode->addAttribute("value", StringUtil::toString(matDens));
        matNode->appendChild(*densNode);

        // Add composition node.
        Element* compNode = new Element("composite");
        compNode->addAttribute("n", "1");
        compNode->addAttribute("ref", elem->GetName());
        matNode->appendChild(*compNode);

        // Add material node to root.
        materials->appendChild((*matNode));
    }

    // Write root node to output stream.
    materials->toXml(out, true, true);
}
