#include "Lexer.h"

/**
 * parseLine(const std::string &line).
 *
 * Operation:
 *  (1). split line into a vector of strings without delimiters
 *  (2). combine any math expressions and operators evaluations
 *  (3). reverse the vector
 *  (4). evaluate each word in the split vector and push the results into an eveluation vector
 *  (5). operate by execution
 *  (6). push into the outQueue
 *
 * @param line ConstStringRef -- a constant ref to a string representing a line of commands.
 * @return a StringsPairsQueue holding the commands to be executed by their order.
 */
StringsPairsQueue Lexer::parseLine(ConstStringRef line) {
    // Local Variables
    StringsPairsQueue outQueue;
    StringsPairsVector evaluationVector;

    // (1).
    StringsVector stringsVector;
    splitStringToVector(line, SPLIT_VECTOR_DELIMITERS, stringsVector, true);
    clearVectorOfEmptyStringsAndSpaces(stringsVector);

    // (2).
    try {
        rejoinAllStringsFromInitializerList(stringsVector, OPERATORS_LIST);
        rejoinAllStringsFromInitializerList(stringsVector, MATH_OPERATIONS);
    } catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }

    // (3).
    std::reverse(stringsVector.begin(), stringsVector.end());

    for(int i = 0; i < stringsVector.size(); ++i) {
        // (4).
        LexerEvalResult evaluation = evaluateString(stringsVector[i]);

        try {
            // (5).
            resultBasedExecution(evaluation, stringsVector, i, evaluationVector);
        } catch(std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }

    // (6).
    vectorToQueue(evaluationVector, outQueue);

    // return.
    return outQueue;
}

/**
 * evaluateString(ConstStringRef str).
 *
 * @param str ConstStringRef -- a const ref to a string
 *
 * @return LexerStringEvaluationResult (enum) representing the string.
 */
LexerEvalResult Lexer::evaluateString(ConstStringRef str) {
    if(str == RAW_OPEN_SERVER_STR)
        return LEXER_PARSE_SERVER_OPEN;

    if(str == RAW_ASSIGN_STR)
        return LEXER_PARSE_ASSIGN;

    if(str == RAW_WHILE_LOOP_STR)
        return LEXER_PARSE_START_WHILE_LOOP;

    if(str == RAW_PRINT_STR)
        return LEXER_PARSE_PRINT;

    if(str == RAW_CONNECT_TO_SEVER_STR)
        return LEXER_PARSE_CONNECT_CLIENT_TO_SERVER;

    if(str == RAW_CREATE_VARIABLE_STR)
        return LEXER_PARSE_CREATE_VARIABLE;

    if(str == RAW_BIND_STR)
        return LEXER_PARSE_BIND_TO;

    if(isPath(str))
        return LEXER_PARSE_PATH;

    // NOTE: isOperator must come BEFORE isMathExpression, for expressions such as:
    //         altitude < 100 * flaps_deg

    // check operator
    if(containsSubstringFromInitializerList(str, OPERATORS_LIST)) {
        return LEXER_PARSE_OPERATOR;
    }

    // check math expression
    if(containsSubstringFromInitializerList(str, MATH_OPERATIONS)) {
        return LEXER_PARSE_MATH_EXPRESSION;
    }

    return LEXER_PARSE_VARIABLE_STR;
}

/**
 * resultBasedExecution(LexerStringEvaluationResult result, StringsList strList,
                                  StringsList::iterator &it, StringsPairsVector &outVector).
 *
 * the function will execute a parsing operation based on the given result.
 *
 * @param result LexerStringEvaluationResult -- a result based on the string pointed by it.
 * @param strList StringsVector -- a vector of strings.
 * @param listIndex int -- an index to the current string
 * @param outVector StringsPairsVector -- a queue of pairs representing <[command_name],[data]>
 */
void Lexer::resultBasedExecution(LexerEvalResult result, StringsVector strVector,
                                  int listIndex, StringsPairsVector &outVector) {
    switch(result) {
        // given a variable or string, simply return, doing nothing with it.
        case LEXER_PARSE_VARIABLE_STR: // skip variables
            return;

        case LEXER_PARSE_PATH: // skip paths
            return;

        case LEXER_PARSE_MATH_EXPRESSION: {
            parseMathExpression(strVector[listIndex], outVector);
            return;
        }

        case LEXER_PARSE_OPERATOR: {
            parseOperatorCommand(strVector[listIndex], outVector);
            return;
        }

        case LEXER_PARSE_CONNECT_CLIENT_TO_SERVER:
            // TODO: add connect to server
            return;

        case LEXER_PARSE_SERVER_OPEN:
            // TODO: add server open
            return;

        case LEXER_PARSE_PRINT:
            // TODO: add parsePrint
            return;

        case LEXER_PARSE_START_WHILE_LOOP:
            // TODO: add parseWhileLoop
            return;

        case LEXER_PARSE_BIND_TO: {
            try {
                parseBindCommand(strVector, listIndex, outVector);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }
            break;
        }

        case LEXER_PARSE_CREATE_VARIABLE: {
            try {
                parseCreateVar(strVector, listIndex, outVector);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }

            break;
        }

        case LEXER_PARSE_ASSIGN: {
            try {
                parseAssignCommand(strVector, listIndex, outVector);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }
            break;
        }

        case LEXER_PARSE_UNKNOWN:
            throw std::runtime_error("Trying to parse unknown type: " + strVector[listIndex] + "\n");
    }
}

/// ---------- UTILITY FUNCTIONS ----------
/**
 * parseBindCommand(const StringsVector &strList, int index, StringsPairsVector &outVector).
 *
 * @param strVec const StringsVector& -- a const reference to a strings vector.
 * @param index int -- an index representing the position of the command string in the vector.
 * @param outVector StringsPairsVector& -- a reference to a StringsPairsVector to modify accordingly.
 */
void Lexer::parseBindCommand(const StringsVector &strVec, int index, StringsPairsVector &outVector) {
    // index is expected to be larger than 1, since there should be a string argument to bind to.
    // therefore, we will check if the index - 1 is within vector range (not -1)
    if(!indexWithinVectorRange(index - 1, strVec))
        throw std::runtime_error("Missing data argument to bind to\n");

    // check that the given argument is indeed a string.
    if(!isPath(strVec[index - 1]))
        throw std::runtime_error("The given argument is not a string. "
                                 "Please make sure to provide a string in the following manner: \"PATH\"");

    // everything is ok -> create a pair containing the command name and data
    outVector.insert(outVector.begin(), makePair<std::string, std::string>(BIND_COMMAND_STR, strVec[index - 1]));
}

/**
 * parseCreateVar(const StringsVector &strVec, int index, StringsPairsVector &outVector).
 *
 * @param strVec const StringsVector& -- a const reference to a vector of strings.
 * @param index int -- an index.
 * @param outVector StringsPairQueue& -- a reference to a StringsPairQueue to modify accordingly.
 */
void Lexer::parseCreateVar(const StringsVector &strVec, int index, StringsPairsVector &outVector) {
    if(!indexWithinVectorRange(index - 1, strVec))
        throw std::runtime_error("Missing variable name to create...\n");

    // if the outVec is not empty ->
    if(!outVector.empty()) {
        // check if the last command pushed is ASSIGN.
        // if so, we will need to push this create var after it.
        if (outVector[0].first == ASSIGN_EXISTING_COMMAND_STR) {
            outVector.insert(
                    outVector.begin() + 1,
                    makePair<std::string, std::string>(
                            RAW_CREATE_VARIABLE_STR, strVec[index - 1]));
            return;
        }
    }

    // otherwise, just insert the createVar at the beginning
    outVector.insert(outVector.begin(), makePair<std::string, std::string>(CREATE_VAR_COMMAND_STR, strVec[index - 1]));
}

/**
 * parseAssignCommand(const StringsVector &strVec, int index, StringsPairsVector &outVector).
 *
 * @param strVec const StringsVec& -- a const reference to a string of vectors.
 * @param index int -- an index.
 * @param outVector StringsPairsVector& -- a reference to a StringsPairsVector to modify accordingly.
 */
void Lexer::parseAssignCommand(const StringsVector &strVec, int index, StringsPairsVector &outVector) {
    // Check that a something was given before the "=" sign
    if(!indexWithinVectorRange(index + 1, strVec))
        throw std::runtime_error("Please provide a variable to assign to. None was provided\n");

    // Check that it was not a path
    if(isPath(strVec[index + 1]))
        throw std::runtime_error("Cannot assign to a path. Please provide a variable\n");

    // Check that a variable was provided
    if(evaluateString(strVec[index + 1]) != LEXER_PARSE_VARIABLE_STR)
        throw std::runtime_error("Cannot assign to a command. Please provide a variable\n");

    // the next item in the list exists, and it is a variable -> create a pair and push it to the queue
    outVector.insert(outVector.begin(), makePair(ASSIGN_EXISTING_COMMAND_STR, strVec[index + 1]));
}

/**
 * parseOperatorCommand(int index, StringsPairsVector &outVec).
 *
 * @param str ConstStringRef str -- a const ref to a string.
 * @param outVector StringsPairsVector& -- a reference to a StringsPairsVector to modify accordingly.
 */
void Lexer::parseOperatorCommand(ConstStringRef str, StringsPairsVector &outVec) {
    // make a string out of the operators initializer list

    StringsVector stringSplit;

    splitStringToVector(str, )

    // check if lhs is a math expression

    // check if rhs is a math expression

    // push a pair to the queue
    outVec.insert(outVec.begin(), makePair(OPERATOR_COMMAND_STR, str));
}

/**
 * parseMathExpression(const std::string &str, StringsPairsVector &outVec)
 *
 * @param str ConstStringRef str -- a const ref to a string.
 * @param outVector StringsPairsVector& -- a reference to a StringsPairsVector to modify accordingly.
 */
void Lexer::parseMathExpression(const std::string &str, StringsPairsVector &outVec) {
    // push a pair to the queue
    outVec.insert(outVec.begin(), makePair(CALCULATE_MATH_COMMAND_STR, str));
}