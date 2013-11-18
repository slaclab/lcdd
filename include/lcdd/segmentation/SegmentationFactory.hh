// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/segmentation/SegmentationFactory.hh,v 1.2 2013-11-14 00:47:23 jeremy Exp $

#ifndef LCDD_SEGMENTATION_SEGMENTATIONFACTORY_HH
#define LCDD_SEGMENTATION_SEGMENTATIONFACTORY_HH 1

class Segmentation;
class SAXObject;

// STL
#include <string>

/**
 * @brief Factory for creating Segmentation objects from SAX objects and their tag names.
 */
class SegmentationFactory {

private:

    /**
     * Class constructor which should not be accessed.
     */
    SegmentationFactory();

public:

    /**
     * Create a Segmentation object from a SAX object and tag name.
     * @param[in] obj The SAXObject of the segmentation.
     * @param[in] tag The segmentation's tag name.
     * @return The Segmentation object.
     */
    static Segmentation* createSegmentation(SAXObject* obj, const std::string& tag);
};

#endif
