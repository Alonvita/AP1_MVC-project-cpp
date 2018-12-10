//
// Created by alon on 06/12/18.
//

#include "UtilityFunctions.h"

/**
 * isNumeric(std::string str).
 *
 * @param str const std::string& -- a reference to a string.
 *
 * @return true if the string contains only digits or '.', or false otherwise.
 *
 * Source: https://stackoverflow.com/questions/7616867/how-to-test-a-string-for-letters-only
 */
bool isNumeric(const std::string &str) {
    bool contains_non_alpha;
    // check negative number
    if(str.size() > 1 && str[0] == '-') {
        contains_non_alpha = str.substr(1).find_first_not_of("1234567890.") != std::string::npos;
    } else {
        contains_non_alpha = str.find_first_not_of("1234567890.") != std::string::npos;
    }


    return !contains_non_alpha;
}

/**
 * splitString(const std::string &inStr, const std::string &sepStr, bool keepSpaces).
 *
 * @param input const std::string & -- the string to parse.
 * @param delimiterStr const std::string & -- all of the delimiters you can think off.
 * @param keepSpaces bool -- true return a list with white spaces, or false otherwise.
 * @param keepDelimiters bool -- true return a list with the delimiters, or false otherwise.
 *
 * @return the parsed string as list, with or withour white spaces.
 */
std::list<std::string> splitString(const std::string &input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters) {
    // Local Variables
    std::list<std::string> output, splitOutput;

    // call split
    splitStringToList(input, delimiterStr, splitOutput, keepDelimiters);

    if (keepSpaces) {
        output = splitOutput;
    } else {
        for (std::string str : splitOutput) {
            if (str.length() > 0 && str != " ") {
                output.push_back(str);
            }
        }
    }

    return output;
}



/**
 * splitStringToList(const std::string &inStr, const std::string& delimiterStr, std::list<std::string> &outList).
 *
 * @param input const std::string & -- the input string.
 * @param delimiterStr const std::string & -- all of the delimiters that you can think of.
 * @param outList std::list<std::string> & -- the output list to modify.
 * @param keepDelimiters bool -- true return a list with the delimiters, or false otherwise.
 *
 */
void splitStringToList(const std::string &input, const std::string& delimiterStr, std::list<std::string> &outList, bool keepDelimiters) {
    // Local Variables
    size_t found, token = 0;
    found = input.find_first_of(delimiterStr); // find the first char in the string that meats any of the separators

    // Run over the string
    while (found != std::string::npos) {
        // push the substring to outList
        outList.push_back(input.substr(token, found - token));
        if(keepDelimiters)
            outList.push_back(input.substr(found, 1));
        // token <- found + 1 (advance token)
        token = found + 1;
        // run the search again
        found = input.find_first_of(delimiterStr, token);
    }

    // push the rest of the string
    outList.push_back(input.substr(token, found - token));
}