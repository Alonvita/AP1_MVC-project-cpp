//
// Created by alon on 09/12/18.
//


#include "OperatorsHandler.h"

/**
 * evaluate_opperation(const std::string &str)
 *
 * @param string const std::string& -- a constant reference to a string.
 * @return a true or false depending on the parameters and the operation.
 */
bool OperatorsHandler::evaluate_operation(ConstStringRef str) {
    std::list<std::string> l;
    std::string delimiter = " ";

    splitStringToList(str, delimiter, l, false);

    // check if size is more than expected
    if(l.size() != 3)
        throw std::runtime_error("Wrong amount of arguments: " + std::to_string(l.size()) + " required 3.");

    // create the variables needed for evaluation
    double lhs;
    double rhs;

    auto it = l.begin();
    ConstStringRef lhsStr = (*(it++));
    ConstStringRef op = (*(it++));
    ConstStringRef rhsStr = (*it);

    // try to give value to lhs
    try {
        giveNumericValueOrGetValFromMap(lhs, lhsStr);
    } catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }

    // try to give value to rhs
    try {
        giveNumericValueOrGetValFromMap(rhs, rhsStr);

        try {
            bool result = evaluate(op, lhs, rhs);

            // both values were given properly -> evaluate
            return result;
        } catch(std::exception& e) {
            throw std::runtime_error(e.what());
        }

    } catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }

}

/**
 * evaluate(const std::string& operation, double lhs, double rhs).
 *
 * @param operation const std::string& -- a constant refrence to a string representing an operator.
 * @param lhs double -- a double value.
 * @param rhs double -- a double value.
 *
 * @return true of false, depending on the values and operation given.
 */
bool OperatorsHandler::evaluate(ConstStringRef operation, double lhs, double rhs) {
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

    std::stringstream ss;

    ss << "Unknown Operand: " + operation;

    throw std::runtime_error(ss.str());
}

/**
 * giveNumericValueOrGetValFromMap(double& out, const std::string& varName).
 *
 * @param out double& -- a reference to a double value to change.
 * @param varName const std::string& -- a reference to a constant string.
 *
 * checks if a number. if so -> turn to double. otherwise, go to variables map
 */
void OperatorsHandler::giveNumericValueOrGetValFromMap(double& out, const std::string& varName) {
    if(isNumeric(varName)) {
        out = stod(varName); // turn to double
    } else {
        VarData* vdata_ptr = this->m_vMap->getVarData(varName); // otherwise, get from map

        if(vdata_ptr == nullptr) {
            std::stringstream msg;
            msg << "The requested variable does not exist: ";
            msg << varName << "\n";

            throw std::runtime_error(msg.str());
        }

        out = *((double*) vdata_ptr->get_data());
    }
}