#include "lcdd/segmentation/SegmentationFactory.hh"

// LCDD
#include "lcdd/schema/grid_xyz.hh"
#include "lcdd/schema/global_grid_xy.hh"
#include "lcdd/schema/nonprojective_cylinder.hh"
#include "lcdd/schema/projective_cylinder.hh"
#include "lcdd/schema/projective_zplane.hh"
#include "lcdd/schema/cell_readout_2d.hh"
#include "lcdd/segmentation/Segmentation.hh"
#include "lcdd/segmentation/GridXYZSegmentation.hh"
#include "lcdd/segmentation/GlobalGridXYSegmentation.hh"
#include "lcdd/segmentation/ProjectiveCylinderSegmentation.hh"
#include "lcdd/segmentation/ProjectiveZPlaneSegmentation.hh"
#include "lcdd/segmentation/NonprojectiveCylinderSegmentation.hh"
#include "lcdd/segmentation/CellReadout2DSegmentation.hh"

// GDML
#include "Saxana/SAXObject.h"
#include "G4Processor/GDMLProcessor.h"
#include "G4Evaluator/GDMLExpressionEvaluator.h"

// STL
#include <iostream>

SegmentationFactory::SegmentationFactory() {
}

Segmentation* SegmentationFactory::createSegmentation(SAXObject* obj, const std::string& tag) {
    Segmentation* seg = 0;
    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

    if (tag == "projective_cylinder") {
        projective_cylinder* prj = dynamic_cast<projective_cylinder*>(obj);
        if (prj) {
            int ntheta, nphi;
            std::string sval = prj->get_ntheta();
            ntheta = (int) calc->Eval(sval);
            sval = prj->get_nphi();
            nphi = (int) calc->Eval(sval);
            seg = new ProjectiveCylinderSegmentation(ntheta, nphi);
        } else {
            std::cerr << "Failed cast to projective_cylinder!" << std::endl;
        }

    } else if (tag == "grid_xyz") {
        // GridXYZ
        grid_xyz* np = dynamic_cast<grid_xyz*>(obj);
        if (np) {
            double gsx, gsy, gsz;
            gsx = gsy = gsz = 0.;
            std::string lunit = np->get_lunit();

            std::string sval = np->get_gridSizeX();
            sval += "*" + lunit;
            gsx = calc->Eval(sval);

            sval = np->get_gridSizeY();
            sval += "*" + lunit;
            gsy = calc->Eval(sval);

            sval = np->get_gridSizeZ();
            sval += "*" + lunit;
            gsz = calc->Eval(sval);

            //std::cout << "grid x, y, z: " << gsx << ", " << gsy << ", " << gsz << std::endl;

            seg = new GridXYZSegmentation(gsx, gsy, gsz);
        } else {
            std::cerr << "Failed cast to grid_xyz!" << std::endl;
        }
    }
    // GlobalGridXY
    else if (tag == "global_grid_xy") {
        global_grid_xy* gridxy = dynamic_cast<global_grid_xy*>(obj);
        if (gridxy) {
            double gsx, gsy;
            gsx = gsy = 0.;
            std::string lunit = gridxy->get_lunit();

            std::string sval = gridxy->get_grid_size_x();
            sval += "*" + lunit;
            gsx = calc->Eval(sval);

            sval = gridxy->get_grid_size_y();
            sval += "*" + lunit;
            gsy = calc->Eval(sval);

            seg = new GlobalGridXYSegmentation(gsx, gsy);
        } else {
            std::cerr << "Failed cast to global_grid_xy!" << std::endl;
        }
    } else if (tag == "nonprojective_cylinder") {
        // handle NP cylinder

        //std::cout << "add nonprojective_cylinder here" << std::endl;

        nonprojective_cylinder* np = dynamic_cast<nonprojective_cylinder*>(obj);
        if (np) {

            double gsp = 0;
            double gsz = 0;

            std::string lunit = np->get_lunit();

            std::string sval = np->get_gridSizePhi();
            sval += "*" + lunit;
            gsp = calc->Eval(sval);

            sval = np->get_gridSizeZ();
            sval += "*" + lunit;
            gsz = calc->Eval(sval);

            seg = new NonprojectiveCylinderSegmentation(gsp, gsz);
        } else {
            std::cerr << "Failed cast to nonprojective_cylinder!" << std::endl;
        }
    } else if (tag == "projective_zplane") {
        // handle projective_zplane

        //std::cout << "add projective_zplane here" << std::endl;

        projective_zplane* prj = dynamic_cast<projective_zplane*>(obj);

        if (prj) {

            int ntheta, nphi;
            std::string sval = prj->get_ntheta();
            ntheta = (int) calc->Eval(sval);
            sval = prj->get_nphi();
            nphi = (int) calc->Eval(sval);

            //std::cout << "ntheta, nphi : " 
            //		<< ntheta << ", " 
            //		<< nphi << std::endl;

            seg = new ProjectiveZPlaneSegmentation(ntheta, nphi);
        } else {
            std::cerr << "Failed cast to projective_zplane!" << std::endl;
        } // prj no exist
    } else if (tag == "cell_readout_2d") {

        //std::cout << "building cell_readout_2d" << std::endl;

        cell_readout_2d* elem = dynamic_cast<cell_readout_2d*>(obj);
        if (0 != elem) {
            double cellSizeX, cellSizeY;
            cellSizeX = cellSizeY = 0;
            std::string lengthUnit = elem->getLengthUnit();

            std::string val = elem->getCellSizeX();
            val += "*" + lengthUnit;
            cellSizeX = calc->Eval(val);

            val = elem->getCellSizeY();
            val += "*" + lengthUnit;
            cellSizeY = calc->Eval(val);

            //std::cout << "G4SegmentationFactory creating CellReadout2DSegmentation(x,y): " << cellSizeX << " " << cellSizeY << std::endl;

            seg = new CellReadout2DSegmentation(cellSizeX, cellSizeY);
        }
    } else {
        // bad segmentation tag
        std::cerr << "Unknown child tag for calorimeter: " << tag << "." << std::endl;
    }

    if (seg == 0) {
        G4Exception("", "", FatalException, "Failed to create segmentation.");
    }

    return seg;
}
