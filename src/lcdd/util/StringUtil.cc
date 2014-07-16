// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/src/lcdd/util/StringUtil.cc,v 1.2 2013-11-13 23:02:59 jeremy Exp $

// LCDD
#include "lcdd/util/StringUtil.hh"

// STL
#include <cctype>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iomanip>

const std::string StringUtil::ALPHA_STR = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string StringUtil::NUM_STR = "1234567890";
const std::string StringUtil::WS_STR = "\x20\x09\x0A\x0B\x0C\x0D";
const std::string StringUtil::NULL_STR = "";

using std::string;
using std::stringstream;
using std::istringstream;
using std::setw;
using std::setfill;
using std::vector;

string StringUtil::toString(double d) {
    stringstream ostr;
    ostr << d;
    return ostr.str();
}

string StringUtil::toString(float f) {
    stringstream ostr;
    ostr << f;
    return ostr.str();
}

string StringUtil::toString(bool b) {
    if (b) {
        return "1";
    }

    return "0";
}

string StringUtil::toString(int i) {
    stringstream ostr;
    ostr << i;
    return ostr.str();
}

string& StringUtil::toLower(string& s) {
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}

string& StringUtil::toLower(const string& s) {
    return StringUtil::toLower(const_cast<string&>(s));
}

double StringUtil::toDouble(string& s) {
    std::istringstream is(s.c_str());
    double d;
    is >> d;
    return d;
}

int StringUtil::toInt(string& s) {
    std::istringstream is(s.c_str());
    int i;
    is >> i;
    return i;
}

bool StringUtil::toBool(string& s) {
    if (StringUtil::toLower(s) == "true" || s == "1") {
        return true;
    } else {
        return false;
    }
}

bool StringUtil::toBool(const string& s) {
    return StringUtil::toBool(const_cast<string&>(s));
}

double StringUtil::toDouble(const string& s) {
    return StringUtil::toDouble(const_cast<string&>(s));
}

void StringUtil::trim(string& str) {
    string::size_type pos = str.find_last_not_of(' ');
    if (pos != string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if (pos != string::npos)
            str.erase(0, pos);
    } else
        str.erase(str.begin(), str.end());
}

string StringUtil::concatStrVec(const vector<string>& s_vec, const string& sep) {
    string r;

    // concat w/ a space in between
    for (vector<string>::const_iterator iter = s_vec.begin(); iter != s_vec.end(); iter++) {
        r += (*iter) + string(sep);
    }

    // lop off dangling space
    r.erase(r.end() - 1, r.end());

    return r;
}

void StringUtil::split(const string& str, const string& delimiters, vector<string>& tokens) {
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {

        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::string StringUtil::replace(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::string StringUtil::pad(std::string input, int width) {
    stringstream ss;
    ss << setfill('0') << setw(width) << input;
    return ss.str();
}
