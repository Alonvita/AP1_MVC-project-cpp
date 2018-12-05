//
// Created by alon_vita on 12/5/18.
//

#include "BinaryExpression.h"

/**
 * getVariables().
 *
 * @return a list<string> of all the variables that this binary expression holds.
 */
template <class T>
std::list<std::string>& BinaryExpression<T>::getVariables() {
    // Local Variables
    std::list<std::string> listVars = std::list<std::string>();
    std::list<std::string> lhsVars = this->lhs.getVariables();
    std::list<std::string> rhsVars = this->rhs.getVariables();

    listVars.insert(listVars.end(), lhsVars.begin(), lhsVars.end());
    listVars.insert(listVars.end(), rhsVars.begin(), rhsVars.end());

    return listVars;
}

template <class T>
Expression& BinaryExpression<T>::assign(const std::string& var, const Expression& expression) {
    auto exp = dynamic_cast<BinaryExpression*>(this);

    // check if this class is of type BinaryExpression
    if(exp == nullptr)
        throw std::runtime_error("This class is not of type BinaryExpression\n");

    // if so.. Assign

}