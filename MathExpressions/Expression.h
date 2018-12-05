//
// Created by alon_vita on 12/5/18.
//

#ifndef MATHUSINGCPP_EXPRESSION_H
#define MATHUSINGCPP_EXPRESSION_H

#include <map>
#include "list"
#include "Exceptions/NotImplementedError.h"
#include "BaseExpression.h"

class Expression {
public:
    /**
    * evaluate(std::map<std::string, double> assignment)
    *
    * Evaluate the expression using the variable values provided
    * in the assignment, and return the result.  If the expression
    * contains a variable which is not in the assignment, an exception
    * is thrown.
    *
    * @throw NotImplementedException.
     *
    * @param assignment std::map<std::string, double> - the variables and their values.
    * @return - returns evaluated expression result.
    */
    virtual double evaluate(std::map<std::string, double>& assignment) throw(IllegalAccess) = 0;

    /**
     * evaluate()
     *
     * A convenience method. Like the `evaluate(assignment)` method above,
     *  but uses an empty assignment.
     *
     * @throw NotImplementedException.
     *
     * @return - returns evaluated expression result.
     */
    virtual double evaluate() throw(IllegalAccess) = 0;

    /**
     * public List<String> getVariables().
     *
     * @return - return a list of the variables in the expression.
     */
    virtual std::list<std::string>& getVariables() = 0;

    /**
     * toString().
     *
     * @return - returns a nice string representation of the expression.
     */
    virtual std::string toString() = 0;

    /**
     * getVariables().
     *
     * all replace all vars occurences with the provided expression.
     *
     * @throw IllegalAccessException.
     *
     * @param var std::string -- variable to replace
     * @param expression Expression -- an Expression
     *
     * @return a new BaseExpression in which all occurrences of std::string var were changed with the given Expression.
     */
    virtual const Expression& assign(std::string var, const Expression& expression) throw(IllegalAccess) = 0;


    /**
     * differentiate().
     *
     * @param var std::string -- differentiating by this expression
     *
     * @return the expression tree resulting from differentiating the current expression relative to variable `var`.
     */
    virtual const Expression& differentiate(std::string var) = 0;

    /**
     * simplify().
     *
     * @throws IllegalAccessException.
     *
     * @return a simplified version of the current expression.
     */
    virtual const Expression& simplify() throw(IllegalAccess) = 0;

};

#endif //MATHUSINGCPP_EXPRESSION_H
