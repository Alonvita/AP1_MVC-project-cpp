//
// Created by alon_vita on 12/5/18.
//

#ifndef MATHUSINGCPP_BINARYEXPRESSION_H
#define MATHUSINGCPP_BINARYEXPRESSION_H


#include "BaseExpression.h"
#include "Expression.h"

template <class T>
class BinaryExpression : public BaseExpression<T> {
public:
    ///---------- CONSTRUCTORS & DESTRUCTORS ----------
    BinaryExpression(const Expression& lhs, const Expression& rhs) : lhs(lhs), rhs(rhs) {};
    ~BinaryExpression() = default;

    ///---------- GETTERS & SETTERS ----------
    const Expression& getLeftExpression()   { return dynamic_cast<const Expression&>(lhs); }
    const Expression& getRightExpression()  { return dynamic_cast<const Expression&>(rhs); }
    std::list<std::string>& getVariables();

    Expression& assign(const std::string& var, const Expression& expression);

private:
    T lhs;
    T rhs;
};


#endif //MATHUSINGCPP_BINARYEXPRESSION_H
