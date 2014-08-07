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
