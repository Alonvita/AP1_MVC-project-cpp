//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_PARSER_H
#define MATHEXPRESSIONS_PARSER_H

#include <map>
#include <list>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fcntl.h> // open
#include <unistd.h> // write
#include <iterator>
#include <algorithm>
#include <sys/stat.h> // open

#include "../VariablesMapContainer.h"
#include "../../Utility/UtilityFunctions.h"

#define DIV_STR "/"
#define PLUS_STR "+"
#define MULT_STR "*"
#define MINUS_STR "-"
#define MODULO_STR "%"

#define ABS_STR "abs"
#define POW_STR "pow"
#define ROOT_STR "root"

#define DELIMITERS "+-*/)("
#define OPERATORS "+-*/"

#define PRECEDENCE_ERROR -1
#define LOW_PRECEDENCE 3
#define MEDIUM_PRECEDENCE 4
#define HIGH_PRECEDENCE 5


class MathExpressionsHandler {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    MathExpressionsHandler(VariablesMapContainer* vMapContainer) : m_vMap(vMapContainer) {};
    ~MathExpressionsHandler() { m_vMap = nullptr; };

    /// ---------- OTHER PUBLIC METHODS ----------
    double parse_mathematical_expression(ConstStringRef rawExpression);

private:
    ///---------- LOCAL VARIABLES ----------
    VariablesMapContainer* m_vMap;

    ///---------- UTILITY FUNCTIONS ----------
    int precedence(const std::string& opL);
    bool isOperator(const std::string& str);
    bool isLeftParentheses(ConstStringRef str);
    bool isRightParentheses(ConstStringRef str);
    double evaluatePostfixList(const StringsList& postfixExpression);
    double getVariableValFromMapOrCreateDoubleForNumericVals(ConstStringRef str);
    void addDummyZeroesBeforeNegationMinus(StringsList & expressionAsList);
    double operateBinaryExpression(ConstStringRef operation, double lhs, double rhs);
    void prefixToPostFix(const StringsList& mathExpressionAsList, StringsList& postfix);

    ///---------- DEBUGGING ----------
    void printExpression(const StringsList& exp);
};


#endif //MATHEXPRESSIONS_PARSER_H
