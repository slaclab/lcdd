#ifndef LCDD_BFIELD_RZBDATA_HH_
#define LCDD_BFIELD_RZBDATA_HH_ 1

/**
 * @brief A single data row for the RZFieldMap.
 * @note Defines radius, z dimension, radial B-field component, and z B-field component.
 */
class RZBData {
public:

    /**
     * Class constructor.
     * @param r  Radius
     * @param z  Z dimension
     * @param Br Radial field strength
     * @param Bz Z dimension field strength
     */
    RZBData(double r, double z, double Br, double Bz);

    /**
     * Class destructor.
     */
    virtual ~RZBData();

public:

    /**
     * Get the radial coordinate.
     * @return The radial coordinate.
     */
    double r() const;

    /**
     * Get the Z coordinate.
     * @return The Z coordinate.
     */
    double z() const;

    /**
     * Get the BR field component.
     * @return The BR field component.
     */
    double Br() const;

    /**
     * Get BZ field component.
     * @return The BZ field component.
     */
    double Bz() const;

private:
    double _r;
    double _z;
    double _Br;
    double _Bz;
};

#endif
