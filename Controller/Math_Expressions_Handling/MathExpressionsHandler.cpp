//
// Created by alon on 06/12/18.
//

#include <vector>
#include <algorithm>
#include "MathExpressionsHandler.h"

/**
 * parse(std::string rawExpression).
 *
 * @param rawExpression std::string -- a string representing a mathematical expression.
 *
 * @return the evaluated expression as a double.
 */
double MathExpressionsHandler::parse_mathematical_expression(const std::string &rawExpression) {

    // split the string into a list w/o spaces and keep delimiters (see function documentation for more info)
    std::list<std::string> expressionAsList =
            splitString(rawExpression, DELIMITERS, false, true);

    // strip from trailing spaces
    for(std::string& str : expressionAsList) {
        std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
        str.erase(end_pos, str.end());
    }

    // handle any negation indicating "-" -> see function documentation for more details
    addDummyZeroesBeforeNegationMinus(expressionAsList);

    // TODO: DEBUG: print expression -> remove this
    printExpression(expressionAsList);

    std::list<std::string> expressionAsPostFix;
    prefixToPostFix(expressionAsList, expressionAsPostFix);

    // TODO: DEBUG: print expression -> remove this
    printExpression(expressionAsPostFix);

    return evaluatePostfixList(expressionAsPostFix);
}

///---------- UTILITY FUNCTIONS ----------

/**
 * prefixToPostFix(const std::list<std::string> mathExpressionAsList).
 *
 * @param mathExpressionAsList const std::list<std::string>& -- a constant reference to a
 *                                                              list<string> representing a prefix math expression.
 * @param postfix std::list<std::string>& -- the list to modify.
 *
 * Pseudo source: http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
 */
void MathExpressionsHandler::prefixToPostFix(
        const std::list<std::string>& mathExpressionAsList,
        std::list<std::string>& postfix) {
    stack<std::string> stack;

    // iterate over the list
    for(std::string str : mathExpressionAsList) {
        // if "(" -> add to stack
        if(isLeftParentheses(str)) {
            stack.push(str);
            continue;
        }

        // if ")"
        if(isRightParentheses(str)) {
            // while stack not empty AND not "("
            while(!stack.empty() && !isLeftParentheses(stack.top())) {
                postfix.push_back(stack.top()); // add to postfix
                stack.pop(); // remove
            }
            stack.pop(); // pop the "("
            continue;
        }

        // if operator
        if(isOperator(str)) {
            // if stack is empty or top item is "("
            if(stack.empty() || isLeftParentheses(stack.top())) {
                stack.push(str); // push it to the stack
            } else {
                while(!stack.empty() &&
                      !isLeftParentheses(stack.top()) &&
                      precedence(str) <= precedence(stack.top())) {
                    // pop and push to the postfix expression
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                // push the operator to the stack
                stack.push(str);
            }
            continue;
        }
        // reaching here means that all "ifs" failed, and this is a variable or a number
        postfix.push_back(str);
    }

    while(!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
    }
}

/**
 * precedence(const std::string &op).
 *
 * @param op const std::string -- a constant string representing an operator;
 *
 * @return the precedence of the operator as an integer as follows:
 *      -,+          : LOW_PRECEDENCE
 *      *,/,%        : MEDIUM_PRECEDENCE
 *      pow,root,abs : HIGH_PRECEDENCE
 *      other        : PRECEDENCE_ERROR
 */
int MathExpressionsHandler::precedence(const std::string &op) {
    if(op == MINUS_STR || op == PLUS_STR)
        return LOW_PRECEDENCE;

    if(op == MULT_STR || op == DIV_STR || op == MODULO_STR)
        return MEDIUM_PRECEDENCE;

    if(op == ROOT_STR || op == POW_STR || op == ABS_STR)
        return HIGH_PRECEDENCE;

    return PRECEDENCE_ERROR;
}

/**
 * isOperand(std::string str).
 *
 * @param str const std::string& -- a reference to a string.
 *
 * @return true if the string contains only digits or '.', or false otherwise.
 *
 * Source: https://stackoverflow.com/questions/7616867/how-to-test-a-string-for-letters-only
 */
bool MathExpressionsHandler::isNumeric(const std::string &str) {
    bool contains_non_alpha;
    // check negative number
    if(str.size() > 1 && str[0] == '-') {
        contains_non_alpha = str.substr(1).find_first_not_of("1234567890.") != std::string::npos;
    } else {
        contains_non_alpha = str.find_first_not_of("1234567890.") != std::string::npos;
    }


    return !contains_non_alpha;
}

/**
 * isOperator(const std::string &str).
 *
 * @param str const std::string& -- a reference to a constant string.
 *
 * @return true if the string is an operand, or false otherwise.
 */
bool MathExpressionsHandler::isOperator(const std::string &str) {
   return(str.find_first_of(OPERATORS) != str.npos);
}

/**
 * isLeftParentheses(const std::string &str).
 *
 * @param str const std::string& -- a reference to a constant string.
 *
 * @return true if the string is "(", or false oterwise.
 */
bool MathExpressionsHandler::isLeftParentheses(const std::string &str) {
    return (str == "(");
}

/**
 * isRightParentheses(const std::string &str).
 *
 * @param str const std::string& -- a reference to a constant string.
 *
 * @return true if the string is ")", or false oterwise.
 */
bool MathExpressionsHandler::isRightParentheses(const std::string &str) {
    return (str == ")");
}

/**
 * getStrLocationInMap(const std::string &str).
 *
 * @param str const std::string & -- a reference to a constant string.
 *
 * @return the iterator location to the string in the map (map.end() if doesn't exist).
 */
map<std::string, var_data*>::iterator MathExpressionsHandler::getStrLocationInMap(const std::string &str) {
    return m_variablesMap.find(str);
}

/**
 * splitStringToList(const std::string &inStr, const std::string& delimiterStr, std::list<std::string> &outList).
 *
 * @param input const std::string & -- the input string.
 * @param delimiterStr const std::string & -- all of the delimiters that you can think of.
 * @param outList std::list<std::string> & -- the output list to modify.
 * @param keepDelimiters bool -- true return a list with the delimiters, or false otherwise.
 *
 */
void MathExpressionsHandler::splitStringToList(const std::string &input, const std::string& delimiterStr, std::list<std::string> &outList, bool keepDelimiters) {
    // Local Variables
    size_t found, token = 0;
    found = input.find_first_of(delimiterStr); // find the first char in the string that meats any of the separators

    // Run over the string
    while (found != string::npos) {
        // push the substring to outList
        outList.push_back(input.substr(token, found - token));
        if(keepDelimiters)
            outList.push_back(input.substr(found, 1));
        // token <- found + 1 (advance token)
        token = found + 1;
        // run the search again
        found = input.find_first_of(delimiterStr, token);
    }

    // push the rest of the string
    outList.push_back(input.substr(token, found - token));
}

/**
 * splitString(const std::string &inStr, const std::string &sepStr, bool keepSpaces).
 *
 * @param input const std::string & -- the string to parse.
 * @param delimiterStr const std::string & -- all of the delimiters you can think off.
 * @param keepSpaces bool -- true return a list with white spaces, or false otherwise.
 * @param keepDelimiters bool -- true return a list with the delimiters, or false otherwise.
 *
 * @return the parsed string as list, with or withour white spaces.
 */
std::list<std::string> MathExpressionsHandler::splitString(const std::string &input, const std::string &delimiterStr, bool keepSpaces, bool keepDelimiters) {
    // Local Variables
    std::list<std::string> output, splitOutput;

    // call split
    splitStringToList(input, delimiterStr, splitOutput, keepDelimiters);

    if (keepSpaces) {
        output = splitOutput;
    } else {
        for (std::string str : splitOutput) {
            if (str.length() > 0 && str != " ") {
                output.push_back(str);
            }
        }
    }

    return output;
}

/**
 * MathExpressionsParser::createExpressionFromPostFixList.
 *
 * @param postfixExpression const std::list<std::string>& -- a const reference to a list<string> representing a postfix expression.
 *
 * @return the evaluated expressions as a double.
 *
 * Pseudo source: http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
 */
double MathExpressionsHandler::evaluatePostfixList(const std::list<std::string> &postfixExpression) {
    stack<std::string> stack;

    // iterate on every string
    for(std::string str : postfixExpression) {
        // operator found
        if(isOperator(str)) {
            // it's a stack so RHS first!
            std::string rhs = stack.top();
            stack.pop(); // used -> pop it

            double rhsD = getVariableValFromMapOrCreateDoubleForNumericVals(rhs);

            // then make LHS
            std::string lhs = stack.top();
            stack.pop(); // used -> pop it

            double lhsD = getVariableValFromMapOrCreateDoubleForNumericVals(lhs);

            // evaluate using the operand and push to the stack.
            stack.push(std::to_string(operateBinaryExpression(str, lhsD, rhsD)));
            continue;
        }

        // reaching here means it's a variable or number.
        stack.push(str);
    }

    // return the double value of the top of the stack (that is the evaluated value)
    return stod(stack.top());
}

/**
 * getVariableValFromMapOrCreateDoubleForNumericVals(const std::string &str).
 * @param str const std::string & -- a const reference to a string.
 *
 * @return str is either numeric or a variable.
 *      If it is numeric -> return stod(str)
 *      else, try to get it from map. an exception should be thrown should we try to reach variablesMap.end()
 *       when the given str does not exist in the variables map.
 */
double MathExpressionsHandler::getVariableValFromMapOrCreateDoubleForNumericVals(const std::string &str) {
    // check numeric
    if(isNumeric(str)) {
        return stod(str);
    }

    try {
        // try to return the variable from the map
        return evaluate((*getStrLocationInMap(str)).second);
        // this would throw an error in case the returned it is at variablesMap.end()
        // then we know that the variable does not exists.
        // This might be handles differently, but for this program's purposes this will do...
    } catch (std::runtime_error& error) {
        cerr << "It is probable that the variable you are trying to extract from the map does not exist\n";
    }
}

/**
 * operateBinaryExpression(const std::string &operation, double lhs, double rhs).
 *
 * @param operation const std::string & -- a string representing a mathematical expression.
 * @param lhs double -- a double.
 * @param rhs double -- a double.
 *
 * @return the result of (lhs OP rhs)
 */
double MathExpressionsHandler::operateBinaryExpression(const std::string &operation, double lhs, double rhs) {
    if (operation == MINUS_STR)
        return lhs - rhs;
    if (operation == PLUS_STR)
        return lhs + rhs;
    if (operation == MULT_STR)
        return lhs * rhs;
    if (operation == DIV_STR)
        return lhs / rhs;
    if (operation == POW_STR)
        return pow(lhs, rhs);
    if(operation == MODULO_STR)
        return ((int)lhs % (int)rhs);
}

/**
 * addDummyZeroesBeforeNegationMinus(std::string &str).
 *
 * This function's purpose is to handle expressions such as:
 *      expression <- -19
 *      expression <- 10 * -y
 * In which the "-" indicates a negation and not an operand.
 *  the function will force push dummy zeroes to compensate.
 *
 * @param str std::string & -- a reference to a string
 */
void MathExpressionsHandler::addDummyZeroesBeforeNegationMinus(std::list<std::string> & expressionAsList) {
    // Local Variables
    bool operandSeparatesTwoOperators = true;
    auto it = expressionAsList.begin();

    // check if expression starts with '-'
    if ((*it) == "-")
        expressionAsList.insert(it++, "0");

    while (it != expressionAsList.end()) {
        // number found
        if(isNumeric(*it))
            operandSeparatesTwoOperators = true; // set true

        // check operator
        if(isOperator(*it)) {
            if(!operandSeparatesTwoOperators) {
                // push 0 before this place
                expressionAsList.insert(it, "(");
                expressionAsList.insert(it, "0");
                ++it;
                ++it;
                expressionAsList.insert(it, ")");
            } else {
                // operator found -> set false unless number was reached
                operandSeparatesTwoOperators = false;
            }
        }

        ++it;
    }
}

/**
 * addToMap(std::string varName, double value).
 *
 * @param varName const std::string& -- a constatnt reference to a string representing a varialbe name.
 * @param value double -- a value
 */
void MathExpressionsHandler::addToMap(const std::string& varName, var_data* varData) {
    this->m_variablesMap.insert(make_pair(varName, varData));

    std::cout << evaluate(this->m_variablesMap.at(varName)) << "\n";
}

/**
 * evaluate(var_data *varData).
 *
 * @param varData var_data* -- a pointer to var_data.
 *
 * @return the double value of the variable, considering it's type.
 */
double MathExpressionsHandler::evaluate(var_data *varData) {
    switch(varData->get_type()) {
        case DOUBLE:
            return *(double*)(varData->get_data());
        case BIND: {
            double value;

            read(*(int*)varData->get_data(), &value, sizeof(double));

            return value;
        }

    }
}

///---------- DEBUGGING ----------
/**
 * printExpression(const std::list<std::string> &exp).
 *
 * @param exp const std::list<std::string> & -- a list<string. representing a mathematical expression
 */
void MathExpressionsHandler::printExpression(const std::list<std::string> &exp) {
    cout << "\n\n---- Expression Print Check BEGIN ---- \n";
    for(std::string s : exp)
        cout << s << " ";
    cout << "\n";
    cout << "---- Expression Print Check END ---- \n";
}