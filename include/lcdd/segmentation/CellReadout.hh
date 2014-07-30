#ifndef LCDD_SEGMENTATION_CELLREADOUT_HH_
#define LCDD_SEGMENTATION_CELLREADOUT_HH_ 1

// STL
#include <vector>
#include <map>
#include <string>

/**
 * @brief Pure virtual base class for calorimeter cell readouts to implement.
 * @todo Move to DDSegmentation package.
 */
class CellReadout {

public:

    /** 2D XY position. */
    struct Position2D {
        double x;
        double y;
    };

    /** Cell ID represented as a pair of int values. */
    struct CellId {
        int ix;
        int iy;
    };

    /** A list of a cell's neighbor IDs. */
    typedef std::vector<CellId> Neighbors;

public:

    /**
     * Class constructor.
     */
    CellReadout();

    /**
     * Class destructor.
     */
    virtual ~CellReadout();

    /**
     * Compute cell ID from local position.
     * @param[in] pos A 2D position.
     * @return A CellId from the position.
     */
    virtual CellId cellId(Position2D pos) = 0;

    /**
     * Compute local position of a cell ID.
     * @param[in] id The cell id.
     * @return The position from the CellId.
     */
    virtual Position2D position(CellId id) = 0;

    /**
     * Create a list of neighbor cells from a cell ID.
     * @param[in] id The cell id.
     * @return The list of Neighbors for the given CellId.
     */
    virtual Neighbors neighbors(CellId id) = 0;
};

#endif
