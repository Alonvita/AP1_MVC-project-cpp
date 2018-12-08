//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_PARSER_H
#define MATHEXPRESSIONS_PARSER_H

#include <map>
#include <list>
#include <stack>
#include <string>
#include <iterator>

#include "Utility/UtilityFunctions.h"
#include "../../Utilities/Reference_Counting/SmartPtr.h"

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

class MathExpressionsParser {
public:
    MathExpressionsParser() { this->m_variablesMap = map<std::string, double>(); };

    void addToMap(const std::string& varName, double value);
    double parse_mathematical_expression(const std::string &rawExpression);


private:
    ///---------- LOCAL VARIABLES ----------
    map<std::string, double> m_variablesMap;

    ///---------- UTILITY FUNCTIONS ----------
    int precedence(const std::string& opL);
    bool isNumeric(const std::string &str);
    bool isOperator(const std::string& str);
    bool isLeftParentheses(const std::string &str);
    bool isRightParentheses(const std::string &str);
    double evaluatePostfixList(const std::list<std::string> &postfixExpression);
    map<std::string, double>::iterator getStrLocationInMap(const std::string &str);
    double getVariableValFromMapOrCreateDoubleForNumericVals(const std::string &str);
    void addDummyZeroesBeforeNegationMinus(std::list<std::string> & expressionAsList);
    double operateBinaryExpression(const std::string &operation, double lhs, double rhs);
    void prefixToPostFix(const std::list<std::string>& mathExpressionAsList, std::list<std::string>& postfix);
    std::list<std::string> splitString(const std::string &input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters);
    void splitStringToList(const std::string &input, const std::string& delimiterStr, std::list<std::string> &outList, bool keepDelimiters);

    ///---------- DEBUGGING ----------
    void printExpression(const std::list<std::string>& exp);
};


#endif //MATHEXPRESSIONS_PARSER_H
