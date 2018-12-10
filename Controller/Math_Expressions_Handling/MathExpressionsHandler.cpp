//
// Created by alon on 06/12/18.
//

#include "MathExpressionsHandler.h"

/**
 * parse(std::string rawExpression).
 *
 * @param rawExpression std::string -- a string representing a mathematical expression.
 *
 * @return the evaluated expression as a double.
 */
double MathExpressionsHandler::parse_mathematical_expression(ConstStringRef rawExpression) {

    // split the string into a list w/o spaces and keep delimiters (see function documentation for more info)
    StringsList expressionAsList = splitString(rawExpression, DELIMITERS, false, true);

    stripStringsListFromSpaces(expressionAsList);

    // handle any negation indicating "-" -> see function documentation for more details
    addDummyZeroesBeforeNegationMinus(expressionAsList);

    StringsList expressionAsPostFix;
    prefixToPostFix(expressionAsList, expressionAsPostFix);
    try {
        return evaluatePostfixList(expressionAsPostFix);
    } catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

///---------- UTILITY FUNCTIONS ----------

/**
 * prefixToPostFix(const StringsList mathExpressionAsList).
 *
 * @param mathExpressionAsList const StringsList& -- a constant reference to a
 *                                                              list<string> representing a prefix math expression.
 * @param postfix StringsList& -- the list to modify.
 *
 * Pseudo source: http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
 */
void MathExpressionsHandler::prefixToPostFix(
        const StringsList& mathExpressionAsList,
        StringsList& postfix) {
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
 * precedence(ConstStringRef op).
 *
 * @param op const std::string -- a constant string representing an operator;
 *
 * @return the precedence of the operator as an integer as follows:
 *      -,+          : LOW_PRECEDENCE
 *      *,/,%        : MEDIUM_PRECEDENCE
 *      pow,root,abs : HIGH_PRECEDENCE
 *      other        : PRECEDENCE_ERROR
 */
int MathExpressionsHandler::precedence(ConstStringRef op) {
    if(op == MINUS_STR || op == PLUS_STR)
        return LOW_PRECEDENCE;

    if(op == MULT_STR || op == DIV_STR || op == MODULO_STR)
        return MEDIUM_PRECEDENCE;

    if(op == ROOT_STR || op == POW_STR || op == ABS_STR)
        return HIGH_PRECEDENCE;

    return PRECEDENCE_ERROR;
}


/**
 * isOperator(ConstStringRef str).
 *
 * @param str ConstStringRef -- a reference to a constant string.
 *
 * @return true if the string is an operand, or false otherwise.
 */
bool MathExpressionsHandler::isOperator(ConstStringRef str) {
   return(str.find_first_of(OPERATORS) != str.npos);
}

/**
 * isLeftParentheses(ConstStringRef str).
 *
 * @param str ConstStringRef -- a reference to a constant string.
 *
 * @return true if the string is "(", or false oterwise.
 */
bool MathExpressionsHandler::isLeftParentheses(ConstStringRef str) {
    return (str == "(");
}

/**
 * isRightParentheses(ConstStringRef str).
 *
 * @param str ConstStringRef -- a reference to a constant string.
 *
 * @return true if the string is ")", or false oterwise.
 */
bool MathExpressionsHandler::isRightParentheses(ConstStringRef str) {
    return (str == ")");
}

/**
 * getStrLocationInMap(ConstStringRef str).
 *
 * @param str ConstStringRef  -- a reference to a constant string.
 *
 * @return the pair given by this map. NOTE: map may also return nullptr if it hasn't found anything.
 */
var_data* MathExpressionsHandler::getVarDataFromMap(ConstStringRef str) {
    return this->m_vMap->getVarData(str);
}

/**
 * MathExpressionsParser::createExpressionFromPostFixList.
 *
 * @param postfixExpression const StringsList& -- a const reference to a list<string> representing a postfix expression.
 *
 * @return the evaluated expressions as a double.
 *
 * Pseudo source: http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
 */
double MathExpressionsHandler::evaluatePostfixList(const StringsList &postfixExpression) {
    stack<std::string> stack;

    // iterate on every string
    for(std::string str : postfixExpression) {
        // operator found
        if(isOperator(str)) {
            // it's a stack so RHS first!
            std::string rhs = stack.top();
            stack.pop(); // used -> pop it

            // try to evaluate rhs
            try {
                double rhsD = getVariableValFromMapOrCreateDoubleForNumericVals(rhs);

                // then make LHS
                std::string lhs = stack.top();
                stack.pop(); // used -> pop it

                // try to evaluate lhs
                try {
                    double lhsD = getVariableValFromMapOrCreateDoubleForNumericVals(lhs);

                    // evaluate using the operand and push to the stack.
                    stack.push(std::to_string(operateBinaryExpression(str, lhsD, rhsD)));
                } catch(std::exception& e) {
                    throw std::runtime_error(e.what());
                }
            } catch(std::exception& e) {
                throw std::runtime_error(e.what());
            }
            continue;
        }

        // reaching here means it's a variable or number.
        stack.push(str);
    }

    // return the double value of the top of the stack (that is the evaluated value)
    return stod(stack.top());
}

/**
 * getVariableValFromMapOrCreateDoubleForNumericVals(ConstStringRef str).
 * @param str ConstStringRef  -- a const reference to a string.
 *
 * @return str is either numeric or a variable.
 *      If it is numeric -> return stod(str)
 *      else, try to get it from map. an exception should be thrown should we try to reach variablesMap.end()
 *       when the given str does not exist in the variables map.
 */
double MathExpressionsHandler::getVariableValFromMapOrCreateDoubleForNumericVals(ConstStringRef str) {
    // check numeric
    if(isNumeric(str)) {
        return stod(str);
    }

    var_data* p = getVarDataFromMap(str);

    if(p == nullptr) {
        std::stringstream ss;
        ss << "Could not find the requested variable in the map: " << str << "\n";

        throw logic_error(ss.str());
    }


    return evaluate(p);

}

/**
 * operateBinaryExpression(ConstStringRef operation, double lhs, double rhs).
 *
 * @param operation ConstStringRef  -- a string representing a mathematical expression.
 * @param lhs double -- a double.
 * @param rhs double -- a double.
 *
 * @return the result of (lhs OP rhs)
 */
double MathExpressionsHandler::operateBinaryExpression(ConstStringRef operation, double lhs, double rhs) {
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
void MathExpressionsHandler::addDummyZeroesBeforeNegationMinus(StringsList& expressionAsList) {
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

///---------- OPERATIONS ----------



///---------- DEBUGGING ----------
/**
 * printExpression(const StringsList &exp).
 *
 * @param exp const StringsList & -- a list<string. representing a mathematical expression.
 *
 */
void MathExpressionsHandler::printExpression(const StringsList& exp) {
    cout << "\n\n---- Expression Print Check BEGIN ---- \n";
    for(std::string s : exp)
        cout << s << " ";
    cout << "\n";
    cout << "---- Expression Print Check END ---- \n";
}