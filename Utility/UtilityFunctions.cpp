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
 * findStringInStringsList(std::list<T>& list, M tofind).
 *
 * @tparam T -- a template of typename T
 * @tparam M -- a template of typename M
 * @param list std::list<T> -- a list of types T.
 *
 * @return return the iterator of the list to target's position. returns list.end() if not found.
 */
template<typename T>
typename std::list<T>::iterator findItemInList(std::list<T> &list, T target) {
    // look for RAW_ASSIGN_STR
    for(auto it = list.begin(); it != list.end(); ++ it) {
        if((*it) == target)
            return it;
    }

    return list.end();
}

/**
 * findItemInListFromList(std::list<T> &list, std::list<T> targetsList).
 *
 * @tparam T -- a template of typename T.
 * @param list std::list<T>& -- a reference to a list of types T
 * @param targetsList std::list<T> -- a list of targets.
 *
 * @return an iterator to the first item found in targetsList that was found in list.
 */
template<typename T>
typename std::list<T>::iterator findFirstItemInListFromList(std::list<T> &list, std::list<T> targetsList) {
    // look for RAW_ASSIGN_STR
    for(auto it = list.begin(); it != list.end(); ++it) {
        for(auto itM = targetsList.begin(); itM != targetsList.end(); ++itM) {
            if ((*it) == (*itM))
                return it;
        }
    }

    return list.end();
}