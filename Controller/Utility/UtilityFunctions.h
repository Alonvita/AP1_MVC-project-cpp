//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <list>
#include <string>
#include <fstream>

enum VarDataType { DOUBLE, BIND, BOOL };

struct var_data {
private:
    void* data;
    VarDataType type;
public:
    void set_data(void* data) { this->data = data; }
    void set_type(VarDataType type) { this->type = type; }

    VarDataType get_type() { return this->type; }
    void* get_data() { return this->data; }
};

bool isNumeric(const std::string &str);
std::list<std::string> splitString(const std::string &input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);
void splitStringToList(const std::string &input, const std::string& delimiterStr, std::list<std::string> &outList, bool keepDelimiters);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
