//
// Created by alon_vita on 12/5/18.
//

#ifndef MATHUSINGCPP_BASICEXPRESSION_H
#define MATHUSINGCPP_BASICEXPRESSION_H


#include <stdexcept>
#include "Exceptions/NotImplementedError.h"

/**
 * BasicExpression.
 *
 * @tparam T template <typename T> -- an object of typename T
 */
template <typename T>
class BaseExpression {
public:
    virtual const T& evaluate() throw(IllegalAccess) = 0;

};

#endif //MATHUSINGCPP_BASICEXPRESSION_H
