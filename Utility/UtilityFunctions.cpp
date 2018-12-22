//
// Created by alon on 06/12/18.
//

#include <iostream>
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
void splitStringToList(const std::string &input, const std::string& delimiterStr, StringsList &outList, bool keepDelimiters) {
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

/**
 * stripStringsListFromSpaced(StringsList& expressionAsList).
 *
 * @param expressionAsList StringsList& -- a reference to a list of strings
 */
void stripStringsListFromSpaces(StringsList& list) {
    // strip from trailing spaces
    for(std::string& str : list) {
        stripStringFromSpaces(str);
    }
}

/**
 * stripStringFromSpaces(std::string& str).
 *
 * @param str std::string& -- a reference to a string.
 */
void stripStringFromSpaces(std::string& str) {
    std::string::iterator end_pos = std::remove_if(str.begin(), str.end(), isspace);
    str.erase(end_pos, str.end());
}

/**
 * flushIteratorsContentToString(const StringsList& strList, StringsList::iterator &it).
 *
 * @param strList const StringsList& -- a constant reference to a StringsList
 * @param it StringsList::iterator& -- a reference to a StringsList's iterator
 *
 * @return a string holding the rest of the list's strings separated by " "
 */
std::string flushListContentToString(const StringsList &strList, StringsList::iterator &it) {
    std::stringstream ss;

    while(it != strList.end()) {
        ss << (*it) << " ";
        ++it;
    }

    return ss.str();
}

/**
 * splitStringToList(const std::string &inStr, const std::string& delimiterStr, std::list<std::string> &outList).
 *
 * @param input const std::string & -- the input string.
 * @param delimiterStr const std::string & -- all of the delimiters that you can think of.
 * @param outList StringsVector& -- the output vector to modify.
 * @param keepDelimiters bool -- true return a list with the delimiters, or false otherwise.
 *
 */
void splitStringToVector(const std::string &input, const std::string& delimiterStr, StringsVector & outVec, bool keepDelimiters) {
    // Local Variables
    size_t found, token = 0;
    found = input.find_first_of(delimiterStr); // find the first char in the string that meats any of the separators

    // Run over the string
    while (found != std::string::npos) {
        // push the substring to outList
        outVec.push_back(input.substr(token, found - token));
        if(keepDelimiters)
            outVec.push_back(input.substr(found, 1));
        // token <- found + 1 (advance token)
        token = found + 1;
        // run the search again
        found = input.find_first_of(delimiterStr, token);
    }

    // push the rest of the string
    outVec.push_back(input.substr(token, found - token));
}

/**
 * bool isGivenStringOfTypeString(ConstStringRef str).
 *
 * @param str ConstStringRef -- a constant reference to a string.
 *
 * @return true if the string is wrapped in " "
 */
bool isPath(const std::string &str) {
    return (str[0] == '\"' && str[str.size() - 1] == '\"');
}

/**
 * clearVectorOfEmptyStrings(StringsVector& vec).
 *
 * @param vec StringsVector& -- a reference to a vector of strings.
 */
void clearVectorOfEmptyStringsNewLinesAndSpaces(StringsVector &vec) {
    for(auto it = vec.begin(); it != vec.end(); ++ it)
        if((*it).empty() || (*it) == " " || (*it) == "\n") {
            vec.erase(it); // erase data
            it--; // go back once since data was erased...
        }
}

/**
 * void rejoinAllOperatorsInStringsVector(std::vector<std::string>& vector).
 *
 * @param vector std::vector<std::string>& -- a reference to a vector of strings.
 */
void rejoinAllStringsFromInitializerList(std::vector<std::string>& vector, std::initializer_list<std::string> initList) {
        std::stringstream reJoin;

        for(auto it = vector.begin(); it != vector.end(); ++ it) {
            // if operand -> combine with left and right
            if(inGivenInitializerList((*it), initList)) {
                // operand in the beginning of the vector
                if(it == vector.begin())
                    throw std::runtime_error("Wrong operand placement: " + (*it) + "\n");

                // rejoin
                reJoin << *(it - 1);
                reJoin << (*it);
                reJoin << *(it + 1);

                // push to vector
                vector.insert(it + 2, reJoin.str());

                // remove rejoined strings from vector
                vector.erase(it - 1);
                vector.erase(it - 1);
                vector.erase(it - 1);

                it--;
                reJoin.str(""); // Clears the stringstream
            }
        }
}

/**
 * bool isOperand(ConstStringRef str).
 *
 * @param str ConstStringRef -- a const ref to a string.
 *
 * @return true if the string is an operand, or false otherwise.
 */
bool inGivenInitializerList(ConstStringRef str, std::initializer_list<std::string> stringsArr) {
    for(auto it = stringsArr.begin(); it != stringsArr.end(); ++it) {
        if (str == (*it)) {
            return true;
        }
    }
    return false;
}

/**
 * bool containsSubstringFromInitializerList(ConstStringRef str, std::initializer_list<std::string> initList).
 *
 * @param str ConstStringRef -- a const ref to a string.
 * @param initList std::initializer_list<std::string> -- an initializer list of strings.
 *
 * @return true if the string contains one of the strings from the list, or false otherwise.
 */
bool containsSubstringFromInitializerList(ConstStringRef str, std::initializer_list<std::string> initList) {
    for(ConstStringRef listStr : initList) {
        if(str.find(listStr) != std::string::npos)
            return true;
    }

    return false;
}

/**
 * initializeListToString(const StringsInitializeList& initList).
 *
 * @param initList const StringsInitializeList& -- a const ref to an init list.
 * @return a string containing the initList.
 */
std::string initializeListToString(const StringsInitializeList& initList) {
    std::stringstream ss;

    for(ConstStringRef listStr : initList)
        ss << listStr;

    return ss.str();
}

/**
 * rejoinAllStringsInVector(StringsVector& stringsVector);
 *
 * @param stringsVector StringsVector& -- a reference to a strings vector.
 */
void rejoinAllStringsInVector(StringsVector& stringsVector) {
    std::stringstream ss;
    auto it = stringsVector.begin();

    for(; it != stringsVector.end(); ++it) {
        if(*it == "\"") {
            do {
                ss << *it << " ";

                stringsVector.erase(it);
            } while(*it != "\"");

            ss << *it; // close the string with a "
            stringsVector.erase(it);
            stringsVector.insert(it, ss.str());
            return;
        }
    }
}