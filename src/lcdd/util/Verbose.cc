// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/util/Verbose.cc,v 1.4 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/util/Verbose.hh"

const Verbose::LevelType Verbose::_defaultLevel = 0;

Verbose::Verbose(LevelType lt) {
    _level = lt;
}

Verbose::~Verbose() {
}

Verbose::LevelType Verbose::verbose() const {
    return _level;
}

void Verbose::setVerbose(LevelType lt) {
    _level = lt;
}
