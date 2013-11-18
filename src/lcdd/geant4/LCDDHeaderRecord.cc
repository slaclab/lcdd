// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/geant4/LCDDHeaderRecord.cc,v 1.2 2013-11-13 23:02:57 jeremy Exp $

// LCDD
#include "lcdd/geant4/LCDDHeaderRecord.hh"

LCDDHeaderRecord::LCDDHeaderRecord() {
}

LCDDHeaderRecord::~LCDDHeaderRecord() {
}

void LCDDHeaderRecord::setDetectorName(const std::string& dn) {
    _detectorName = dn;
}

void LCDDHeaderRecord::setDetectorVersion(const std::string& dv) {
    _detectorVersion = dv;
}

void LCDDHeaderRecord::setDetectorUrl(const std::string& u) {
    _detectorUrl = u;
}

void LCDDHeaderRecord::setAuthorName(const std::string& an) {
    _authorName = an;
}

void LCDDHeaderRecord::setGeneratorName(const std::string& gn) {
    _generatorName = gn;
}

void LCDDHeaderRecord::setGeneratorVersion(const std::string& gv) {
    _generatorVersion = gv;
}

void LCDDHeaderRecord::setGeneratorChecksum(const std::string& c) {
    _generatorChecksum = c;
}

void LCDDHeaderRecord::setGeneratorFile(const std::string& gurl) {
    _generatorFile = gurl;
}

void LCDDHeaderRecord::setAuthorEmail(const std::string& ae) {
    _authorEmail = ae;
}

void LCDDHeaderRecord::setComment(const std::string& c) {
    _comment = c;
}

void LCDDHeaderRecord::setChecksum(const std::string& c) {
    _generatorChecksum = c;
}

const std::string& LCDDHeaderRecord::getDetectorName() const {
    return _detectorName;
}

const std::string& LCDDHeaderRecord::getDetectorVersion() const {
    return _detectorVersion;
}

const std::string& LCDDHeaderRecord::getDetectorUrl() const {
    return _detectorUrl;
}

const std::string& LCDDHeaderRecord::getComment() const {
    return _comment;
}

const std::string& LCDDHeaderRecord::getAuthorName() const {
    return _authorName;
}

const std::string& LCDDHeaderRecord::getAuthorEmail() const {
    return _authorEmail;
}

const std::string& LCDDHeaderRecord::getGeneratorName() const {
    return _generatorName;
}

const std::string& LCDDHeaderRecord::getGeneratorVersion() const {
    return _generatorVersion;
}

const std::string& LCDDHeaderRecord::getGeneratorFile() const {
    return _generatorFile;
}

const std::string& LCDDHeaderRecord::getGeneratorChecksum() const {
    return _generatorChecksum;
}

std::ostream& LCDDHeaderRecord::printOut(std::ostream &os) {
    os << std::endl << "***** LCDD Header *****" << std::endl;

    os << "detectorName <" << _detectorName << ">" << std::endl;
    os << "detectorVersion <" << _detectorVersion << ">" << std::endl;
    os << "detectorUrl <" << _detectorUrl << ">" << std::endl;
    os << "authorName <" << _authorName << ">" << std::endl;
    os << "authorEmail <" << _authorEmail << ">" << std::endl;
    os << "generatorName <" << _generatorName << ">" << std::endl;
    os << "generatorVersion <" << _generatorVersion << ">" << std::endl;
    os << "generatorFile <" << _generatorFile << ">" << std::endl;
    os << "generatorChecksum <" << _generatorChecksum << ">" << std::endl;
    os << "comment" << std::endl << _comment << std::endl << "end comment" << std::endl;

    os << "***********************" << std::endl << std::endl;
    return os;
}
