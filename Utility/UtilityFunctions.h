//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "../DefinesAndTypedefs.h"

bool isNumeric(const std::string &str);
void stripStringFromSpaces(std::string& str);
void stripStringsListFromSpaces(StringsList& list);
std::string flushListContentToString(const StringsList &strList, StringsList::iterator &it);
void splitStringToList(ConstStringRef input, ConstStringRef delimiterStr, StringsList &outList, bool keepDelimiters);
std::list<std::string> splitString(ConstStringRef input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);

/// ------ GENERIC FUNCTIONS ------
template<typename T>
typename std::list<T>::iterator findItemInList(std::list<T> &list, T target);

template<typename T>
typename std::list<T>::iterator findItemInListFromList(std::list<T> &list, std::list<T> targetsList);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
