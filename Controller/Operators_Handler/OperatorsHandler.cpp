//
// Created by alon on 09/12/18.
//


#include "OperatorsHandler.h"

/**
 * evaluate(const std::string& operation, double lhs, double rhs).
 *
 * @param operation const std::string& -- a constant refrence to a string representing an operator.
 * @param lhs double -- a double value.
 * @param rhs double -- a double value.
 *
 * @return true of false, depending on the values and operation given.
 */
bool evaluate(const std::string& operation, double lhs, double rhs) {
    if(operation == LT)
        return lhs < rhs;
    if(operation == GT)
        return lhs > rhs;
    if(operation == LE)
        return lhs <= rhs;
    if(operation == GE)
        return lhs >= rhs;
    if(operation == EQ)
        return lhs == rhs;

    return false;
}