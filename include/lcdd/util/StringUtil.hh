// $Header: /nfs/slac/g/lcd/cvs/lcdroot/lcdd/include/lcdd/util/StringUtil.hh,v 1.6 2013-11-14 00:47:23 jeremy Exp $

#ifndef LCDD_UTIL_STRINGUTIL_HH
#define LCDD_UTIL_STRINGUTIL_HH 1

// STL
#include <string>
#include <sstream>
#include <vector>

/**
 * @brief A collection of various static string utility functions.
 */
class StringUtil {

private:

    /**
     * Class constructor.
     * Should not be instantiated.
     */
    virtual ~StringUtil() {
    }

public:

    // a-zA-Z
    static const std::string ALPHA_STR;

    // 0-9
    static const std::string NUM_STR;

    // std. whitespace; 0x09-0D and 20
    static const std::string WS_STR;

    // null string
    static const std::string NULL_STR;

public:

    /**
     * Convert double value to string.
     * @param[in] d The double value.
     * @return The string value.
     */
    static std::string toString(double d);

    /**
     * Convert float value to string.
     * @param[in] f The float value.
     * @return The string value.
     */
    static std::string toString(float f);

    /**
     * Convert int value to string.
     * @param[in] i The int value.
     * @return The string value.
     */
    static std::string toString(int i);

    /**
     * Convert bool value to string.
     * @param[in] b The bool value.
     * @return The string value.
     */
    static std::string toString(bool b);

    /**
     * Convert string to all lower case.
     * @param[in] s The string to be converted.
     * @return The string converted to all lower case.
     */
    static std::string& toLower(std::string& s);

    /**
     * Convert string to all lower case, const version.
     * @param[in] s The string to be converted.
     * @return The string converted to all lower case.
     */
    static std::string& toLower(const std::string& s);

    /**
     * Convert string to double value.
     * @param[in] s The string to be converted.
     * @return The converted double value.
     */
    static double toDouble(std::string& s);

    /**
     * Convert string to double value, const version.
     * @param[in] s The string to be converted.
     * @return The converted double value.
     */
    static double toDouble(const std::string& s);

    /**
     * Convert string to int value.
     * @param[in] s The string to be converted.
     * @return The converted in value.
     */
    static int toInt(std::string& s);

    /**
     * Convert string to bool value.
     * @param[in] s The string to be converted.
     * @return The converted bool value.
     */
    static bool toBool(std::string& s);

    /**
     * Convert string to bool value, const version.
     * @param[in] s The string to be converted.
     * @return The converted bool value.
     */
    static bool toBool(const std::string& s);

    /**
     * Trim whitespace from string.
     * @param[out] str Trim whitespace from string, in place.
     */
    static void trim(std::string& str);

    /**
     * Concatenate a vector of strings into one string, separated by sep character.
     * @param[in] strings The vector of strings.
     * @param[in] sep     The separator between elements.
     */
    static std::string concatStrVec(const std::vector<std::string>& strings, const std::string& sep = " ");

    /**
     * Split a string into tokens based on list of delimiters.
     * @param[in]  str        The string to be split.
     * @param[in]  delimiters The list of single character delimiters.
     * @param[out] tokens     The output list of string tokens.
     */
    static void split(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens);
};

#endif
