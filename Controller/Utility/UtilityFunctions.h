//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include "../../DefinesAndTypedefs.h"

enum VarDataType { DOUBLE, BIND, BOOL };

struct var_data {
private:
    void* data;
    VarDataType type;
public:
    ~var_data() {
        if(this->type != BOOL)
            free(this->data);
    }

    void set_data(void* data) {
        this->data = data;
    }

    void set_type(VarDataType type) { this->type = type; }

    VarDataType get_type() { return this->type; }
    void* get_data() { return this->data; }
};

bool isNumeric(const std::string &str);
void stripStringFromSpaces(std::string& str);
void stripStringsListFromSpaces(StringsList& list);
std::list<std::string> splitString(ConstStringRef input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);
void splitStringToList(ConstStringRef input, ConstStringRef delimiterStr, StringsList &outList, bool keepDelimiters);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
