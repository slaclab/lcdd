// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/util/Verbose.hh,v 1.5 2013-11-14 00:47:23 jeremy Exp $
#ifndef LCDD_UTIL_VERBOSE_HH
#define LCDD_UTIL_VERBOSE_HH 1

/**
 * @brief Mixin class for setting and retrieving verbosity level.
 * @todo Move code to source file.
 */
class Verbose {

public:
    typedef unsigned int LevelType;

public:

    /**
     * Class constructor.
     */
    Verbose(LevelType lt = _defaultLevel);

    /**
     * Class destructor.
     */
    virtual ~Verbose();

public:

    /**
     * Get the verbosity level.
     * @return The verbosity level.
     */
    virtual inline LevelType verbose() const;

    /**
     * Set the verbosity level.
     * @param[in] lt The new verbosity level.
     */
    virtual inline void setVerbose(LevelType lt);

protected:
    LevelType _level;
    static const LevelType _defaultLevel;
};

#endif
