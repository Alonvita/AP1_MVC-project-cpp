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

bool isPath(ConstStringRef str);
bool isNumeric(const std::string &str);
void stripStringFromSpaces(std::string& str);
void stripStringsListFromSpaces(StringsList& list);
void clearVectorOfEmptyStringsAndSpaces(StringsVector &vec);
bool inGivenInitializerList(ConstStringRef str, std::initializer_list<std::string>);
bool containsSubstringFromInitializerList(ConstStringRef str, std::initializer_list<std::string> initList);
void splitStringToList(ConstStringRef input, ConstStringRef delimiterStr, StringsList &outList, bool keepDelimiters);
void rejoinAllStringsFromInitializerList(std::vector<std::string>& vector, std::initializer_list<std::string> stringsArr);
std::list<std::string> splitString(ConstStringRef input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);
void splitStringToVector(const std::string &input, const std::string& delimiterStr, StringsVector & outVec, bool keepDelimiters);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H