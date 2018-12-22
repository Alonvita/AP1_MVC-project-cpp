//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
#define AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H

#include <list>
#include <string>
#include <sstream>

#include "../../Utility/UtilityFunctions.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

class OperatorsHandler {
public:
    explicit OperatorsHandler(MathExpressionsHandler* mathExpressionsHandler) : m_handler(mathExpressionsHandler) {};

    bool evaluate_operation(const std::string &str);
    void calculateExpression(double &, const std::string &);

private:
    MathExpressionsHandler* m_handler;

    bool evaluate(const std::string& operation, double lhs, double rhs);
};


#endif //AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
