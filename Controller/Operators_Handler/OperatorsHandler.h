//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
#define AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H

#include <string>

#define LT "<"
#define GT ">"
#define LE "<="
#define GE ">="
#define EQ "=="

class OperatorsHandler {
public:
    bool evaluate(const std::string& operation, double lhs, double rhs);
};


#endif //AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
