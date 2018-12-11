//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include "../DefinesAndTypedefs.h"

bool isNumeric(const std::string &str);
void stripStringFromSpaces(std::string& str);
void stripStringsListFromSpaces(StringsList& list);
void splitStringToList(ConstStringRef input, ConstStringRef delimiterStr, StringsList &outList, bool keepDelimiters);
std::list<std::string> splitString(ConstStringRef input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
