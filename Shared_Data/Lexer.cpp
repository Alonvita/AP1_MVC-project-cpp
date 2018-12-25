#include "Lexer.h"

/**
 * parseFlightGearData(StringsVector& outVec).
 *
 * @param vec StringsVector& -- a ref to a vector of strings.
 */
void Lexer::parseFlightGearData(const StringsVector& vec, CommandDataQueue& outQueue) {
    std::initializer_list<std::string> stringsList = FLIGHTGEAR_VALUES_INITIALIZER_LIST;

    unsigned long listSize = std::min(stringsList.size(), vec.size());

    for(unsigned long i = 0; i < listSize; ++i) {

        outQueue.push(new CommandData(UPDATE_EXISTING_COMMAND_STR ,*(stringsList.begin() + i) + " " + vec[i]));
    }
}

/**
 * parseLine(const std::string &line).
 *
 * Operation:
 *  (1). split line into a vector of strings without delimiters
 *  (2). combine any math expressions and operators evaluations
 *  (3). reverse the vector
 *  (4). evaluate each word in the split vector and push the results into an eveluation vector
 *  (5). operate by execution into placeHolder or evaluationVector.
 *  (6). if m_readToPlaceHolder == true -> return
 *  (7). (otherwise) push into the outQueue
 *
 * @param line ConstStringRef -- a constant ref to a string representing a line of commands.
 * @param outQueue CommandDataQueue& -- a reference to a commands data queue to add commands to.
 */
void Lexer::parseLine(ConstStringRef line, CommandDataQueue& outQueue) {
    // (1).
    StringsVector stringsVector;
    splitStringToVector(line, LEXER_SPLIT_DELIMITERS, stringsVector, true);
    clearVectorOfEmptyStringsNewLinesAndSpaces(stringsVector);

    // (2).
    try {
        rejoinAllStringsInVector(stringsVector);
        rejoinAllStringsFromInitializerList(stringsVector, OPERATORS_LIST);
        rejoinAllStringsFromInitializerList(stringsVector, MATH_OPERATIONS);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }

    // (3).
    std::reverse(stringsVector.begin(), stringsVector.end());

    for (unsigned i = 0; i < stringsVector.size(); ++i) {
        // (4).
        LexerEvalResult evaluation = evaluateString(stringsVector[i]);
        try {
            // (5).
            resultBasedExecution(evaluation, stringsVector, i, m_placeHolder[0]);
        } catch (std::exception &e) {
            throw std::runtime_error(e.what());
        }
    }
    if (!m_curlyBracketsFound && m_readToPlaceHolder == 0) {
        // PUSH
        pushFromVectorToQueue(m_placeHolder[0], outQueue);

        // CLEAR placeHolder[0]
        m_placeHolder[0].clear();
    }
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

    if(str == RAW_SLEEP_STR)
        return LEXER_PARSE_SLEEP_COMMAND;

    if(str == RAW_BIND_STR)
        return LEXER_PARSE_BIND_TO;

    if(isPath(str))
        return LEXER_PARSE_PATH;

    if(str == RAW_OPEN_BRACKETS)
        return LEXER_PARSE_OPEN_CURLY_BRACKETS;

    if(str == RAW_CLOSE_BRACKETS)
        return LEXER_PARSE_CLOSE_CURLY_BRACKETS;

    if(str == RAW_CLOSE_COMMAND_STR)
        return LEXER_PARSE_CLOSE_COMMAND;

    if(str == RAW_IF_COMMAND_STR)
        return LEXER_PARSE_IF_COMMAND;

    // NOTE: isOperator must come BEFORE isMathExpression, for expressions such as:
    //         altitude < 100 * flaps_deg

    // check operator
    if(containsSubstringFromInitializerList(str, OPERATORS_LIST)) {
        return LEXER_PARSE_OPERATOR;
    }

    // check math expression or numeric value
    if(containsSubstringFromInitializerList(str, MATH_OPERATIONS) ||
        isNumeric(str)) {
        return LEXER_PARSE_MATH_EXPRESSION;
    }

    return LEXER_PARSE_VARIABLE_STR;
}

/**
 * resultBasedExecution(LexerStringEvaluationResult result, StringsList strList,
                                  StringsList::iterator &it, CommandDataVector &outVector).
 *
 * the function will execute a parsing operation based on the given result.
 *
 * @param result LexerStringEvaluationResult -- a result based on the string pointed by it.
 * @param strList StringsVector -- a vector of strings.
 * @param listIndex int -- an index to the current string
 * @param outVector CommandDataVector -- a queue of pairs representing <[command_name],[data]>
 */
void Lexer::resultBasedExecution(LexerEvalResult result, StringsVector& strVector,
                                  int listIndex, CommandDataVector &outVector) {
    // if m_readToPlaceHolder > 0 -> create an alias to that placeHolder. Otherwise,
    //  take outVector as an alias
    CommandDataVector& outVecAlias =
            m_readToPlaceHolder > 0 ? m_placeHolder[m_readToPlaceHolder] : outVector;


    switch(result) {
        // given a variable or string, simply return, doing nothing with it.
        case LEXER_PARSE_VARIABLE_STR: // skip variables
            return;

        case LEXER_PARSE_SLEEP_COMMAND: {
            parseSleepCommand(outVecAlias);
            break;
        }

        case LEXER_PARSE_PATH: {
            std::string& filePath = strVector[listIndex];

            // clear from \" and spaces
            filePath.erase(std::remove(filePath.begin(), filePath.end(), '\"'), filePath.end());
            filePath.erase(std::remove(filePath.begin(), filePath.end(), ' '), filePath.end());
            return;
        }

        case LEXER_PARSE_OPEN_CURLY_BRACKETS: {
            m_openBracketsCount++;
            m_readingSection = true;
            m_curlyBracketsFound = true;
            return;
        }

        case LEXER_PARSE_MATH_EXPRESSION: {
            parseMathExpression(strVector[listIndex], outVecAlias);
            return;
        }

        case LEXER_PARSE_IF_COMMAND: {
            parseIfCommand(outVecAlias);
            return;
        }

        case LEXER_PARSE_OPERATOR: {
            parseOperatorCommand(strVector[listIndex], outVecAlias);
            return;
        }

        case LEXER_PARSE_CONNECT_CLIENT_TO_SERVER:
            connectClientToServer(strVector, listIndex, outVecAlias);
            return;

        case LEXER_PARSE_SERVER_OPEN:
            openServer(strVector, listIndex, outVecAlias);
            return;

        case LEXER_PARSE_PRINT: {
            parsePrintCommand(strVector, listIndex, outVecAlias);
            return;
        }

        case LEXER_PARSE_START_WHILE_LOOP: {
            parseWhileLoopToQueue(outVecAlias);
            return;
        }

        case LEXER_PARSE_BIND_TO: {
            try {
                parseBindCommand(strVector, listIndex, outVecAlias);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }
            return;
        }

        case LEXER_PARSE_CREATE_VARIABLE: {
            try {
                parseCreateVar(strVector, listIndex, outVecAlias);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }

            return;
        }

        case LEXER_PARSE_ASSIGN: {
            try {
                parseAssignCommand(strVector, listIndex, outVecAlias);
            } catch(std::exception& e) {
                throw(std::runtime_error(e.what()));
            }
            return;
        }

        case LEXER_PARSE_CLOSE_COMMAND: {
            parseCloseCommand(strVector[listIndex], outVecAlias);
            return;
        }

        case LEXER_PARSE_CLOSE_CURLY_BRACKETS: {
            // increase '}' count
            m_closeBracketsCount++;

            // check '{' == '}'
            if(m_closeBracketsCount == m_openBracketsCount)
                m_readingSection = false;

            if(outVecAlias.empty())
                throw std::runtime_error("No commands were assigned before receiving '}'\n");

            // point to the first command in the last placeholder
            CommandData* assignTo = (m_placeHolder[m_readToPlaceHolder - 1])[0];

            assignCommandWithPlaceHolder(assignTo);
            return;
        }

        case LEXER_PARSE_UNKNOWN:
            throw std::runtime_error("Trying to parse unknown type: " + strVector[listIndex] + "\n");
    }
}

/// ---------- UTILITY FUNCTIONS ----------
/**
 * parseBindCommand(const StringsVector &strList, int index, CommandDataVector &outVector).
 *
 * @param strVec const StringsVector& -- a const reference to a strings vector.
 * @param index int -- an index representing the position of the command string in the vector.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseBindCommand(const StringsVector &strVec, int index, CommandDataVector &outVector) {
    // index is expected to be larger than 1, since there should be a string argument to bind to.
    // therefore, we will check if the index - 1 is within vector range (not -1)
    if(!indexWithinVectorRange(index - 1, strVec))
        throw std::runtime_error("Missing data argument to bind to\n");

    outVector.insert(outVector.begin(), new CommandData(BIND_COMMAND_STR, strVec[index - 1]));

}

/**
 * parseCreateVar(const StringsVector &strVec, int index, CommandDataVector &outVector).
 *
 * @param strVec const StringsVector& -- a const reference to a vector of strings.
 * @param index int -- an index.
 * @param outVector CommandDataQueue& -- a reference to a CommandDataQueue to modify accordingly.
 */
void Lexer::parseCreateVar(const StringsVector &strVec, int index, CommandDataVector &outVector) {
    if(!indexWithinVectorRange(index - 1, strVec))
        throw std::runtime_error("Missing variable name to create...\n");

    // if the outVec is not empty ->
    if(!outVector.empty()) {
        // should the last command pushed is ASSIGN, the var will come before assign and calculation.
        if (outVector[0]->getName() == ASSIGN_EXISTING_COMMAND_STR) {
            outVector.insert(
                    outVector.end(),
                    new CommandData(
                            CREATE_VAR_COMMAND_STR,
                            strVec[index - 1]));
            return;
        }
    }

    // otherwise, just insert the createVar at the beginning
    outVector.insert(outVector.begin(), new CommandData(CREATE_VAR_COMMAND_STR, strVec[index - 1]));
}

/**
 * parseAssignCommand(const StringsVector &strVec, int index, CommandDataVector &outVector).
 *
 * @param strVec const StringsVec& -- a const reference to a string of vectors.
 * @param index int -- an index.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseAssignCommand(const StringsVector &strVec, int index, CommandDataVector &outVector) {
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
    outVector.insert(outVector.begin(), new CommandData(ASSIGN_EXISTING_COMMAND_STR, strVec[index + 1]));
}

/**
 * parseOperatorCommand(int index, CommandDataVector &outVec).
 *
 * @param str ConstStringRef str -- a const ref to a string.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseOperatorCommand(ConstStringRef str, CommandDataVector &outVector) {
    // make a string out of the operators initializer list
    std::string operatorsAsDelimitersList = initializeListToString(OPERATORS_LIST);

    // Local Variable
    StringsVector stringSplit;

    // split the string to a vector holding: [LHS] -- [OPERATOR] -- [RHS]
    splitStringToVector(str, operatorsAsDelimitersList, stringSplit, true);

    if(stringSplit.size() > 3)
        throw std::runtime_error("We are sorry, but the program doesn't currently support chained conditions... How'bout you try Python instead?\n");

    outVector.insert(outVector.begin(), new CommandData(OPERATOR_COMMAND_STR, str));
}

/**
 * parseMathExpression(const std::string &str, CommandDataVector &outVec)
 *
 * @param str ConstStringRef str -- a const ref to a string.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseMathExpression(const std::string &str, CommandDataVector &outVector) {
    // push a pair to the queue
    outVector.insert(outVector.begin(), new CommandData(CALCULATE_MATH_COMMAND_STR, str));
}

/**
 * parseIfCommand(const StringsVector &strVec, int index, CommandDataVector &outVec).
 *
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseIfCommand(CommandDataVector &outVec) {
    if(!(outVec[0]->getName() == OPERATOR_COMMAND_STR))
        throw std::runtime_error("Could not find a condition when parsing if command\n");

    // set the name of the operator command to an IF command
    outVec[0]->setName(IF_COMMAND_STR);

    // if curly brackets were found
    if (m_curlyBracketsFound) {
        createNewPlaceHolder();
    } else {
        // otherwise -> treat as 1 life if.
        throw std::runtime_error("Our apology, one line ifs are not implemented in this version\n");
    }
}


/**
 * parseCloseCommand(ConstStringRef command, CommandDataVector &outVec).
 *
 * @param str ConstStringRef str -- a const ref to a string.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseCloseCommand(ConstStringRef command, CommandDataVector &outVec) {
    outVec.insert(outVec.begin(), new CommandData(CLOSE_COMMAND_STR, command));
}

/**
 * parsePrintCommand(const StringsVector &strVec, int index, CommandDataVector &outVec).
 *
 * @param strVec const StringsVec& -- a const reference to a string of vectors.
 * @param index int -- an index.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parsePrintCommand(const StringsVector &strVec, int index, CommandDataVector &outVec) {
    if(!indexWithinVectorRange(index - 1, strVec))
        throw std::runtime_error("Required string argument to print command\n");

    std::string command = strVec[index - 1];

    if(!isPath(command))
        throw std::runtime_error("Please provide print command with a string\n");

    outVec.insert(outVec.begin(), new CommandData(PRINT_COMMAND_STR, command));
}

/**
 * parseWhileLoopToQueue(const StringsVector &strVec, int index, CommandDataVector &outVec).
 *
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseWhileLoopToQueue(CommandDataVector &outVec) {
    if(!(outVec[0]->getName() == OPERATOR_COMMAND_STR))
        throw std::runtime_error("Could not find a condition when parsing if command\n");

    // set the name of the operator command to an IF command
    outVec[0]->setName(WHILE_LOOP_COMMAND_STR);


    if(m_curlyBracketsFound) {
        createNewPlaceHolder();
    } else {
        // otherwise -> treat as 1 life if.
        throw std::runtime_error("Our apology, one line while loops are not implemented in this version\n");
    }
}

/**
 * parseSleepCommand(const std::string &str, CommandDataVector &outVec).
 *
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::parseSleepCommand(CommandDataVector &outVec) {
    if(!(outVec[0]->getName() == CALCULATE_MATH_COMMAND_STR))

    // set the name of the command to an SLEEP command
    outVec[0]->setName(OPEN_SERVER_COMMAND_STR);
}

/**
 * openServer(const StringsVector &strVec, int index, CommandDataVector &outVec).
 *
 * @param strVec const StringsVec& -- a const reference to a string of vectors.
 * @param index int -- an index.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
void Lexer::openServer(const StringsVector &strVec, int index, CommandDataVector &outVec) {
    if(2 < outVec.size() || outVec.size() == 0) {
        throw std::runtime_error("Command's call convention is: \"openDataServer\" [PORT] [READS PER SECOND]\n");
    }

    if(!isNumeric(outVec[0]->getData())) {
        throw std::runtime_error("Command's call convention is: \"openDataServer\" [PORT] [READS PER SECOND]\n");
    }

    std::string readsPerSec;
    std::string port = outVec[0]->getData(); // set the port
    SAFELY_REMOVE_COMMAND_DATA_VEC_BEGIN(outVec);

    if(outVec.size() == 1) {
        if(!isNumeric(outVec[1]->getData()))
            throw std::runtime_error("Command's call convention is: \"openDataServer\" [PORT] [READS PER SECOND]\n");

        readsPerSec = outVec[1]->getData();
        SAFELY_REMOVE_COMMAND_DATA_VEC_BEGIN(outVec);
    }

    std::stringstream command;
    command << port;

    if(!readsPerSec.empty()) {
        command << " " << readsPerSec;
    } else {
        command << " " << DEFAULT_READS_PER_SECOND_STR; // default reads per second...
    }

    // push the open server command
    outVec.insert(outVec.begin(), new CommandData(OPEN_SERVER_COMMAND_STR, command.str()));
}

/**
 * connectClientToServer(const StringsVector &strVec, int index, CommandDataVector &outVec).
 *
 * @param strVec const StringsVec& -- a const reference to a string of vectors.
 * @param index int -- an index.
 * @param outVector CommandDataVector& -- a reference to a CommandDataVector to modify accordingly.
 */
 void Lexer::connectClientToServer(const StringsVector &strVec, int index, CommandDataVector &outVec) {
     if(outVec.size() != 1) {
         throw std::runtime_error("Command's call convention is: \"connect\" [IP_ADDRESS] [PORT]\n");
     }

     if(!isValidIPAddress(strVec[index - 1])) {
         throw std::runtime_error("Please provide a valid IP address of type IPv4: xxx.xxx.xxx.xxx\n");
     }

    if (!isNumeric(outVec[0]->getData())) {
        throw std::runtime_error("Please provide a port. Command's call convention is: \"connect\" [IP_ADDRESS] [PORT]\n");
    }

    std::string IP = strVec[index - 1]; // take the IP address
    std::string port = outVec[0]->getData(); // take the port


    std::stringstream command;
    command << IP << " " << port;

    // clear the vector -> commands will not be needed
    SAFELY_REMOVE_COMMAND_DATA_VEC_BEGIN(outVec);

    // push the open server command
    outVec.insert(outVec.begin(), new CommandData(CONNECT_TO_SERVER_COMMAND_STR, command.str()));
}

/// ---------- PRIVATE METHODS ----------
/**
 * assignCommandWithPlaceHolder(CommandData &command).
 *
 * @param command CommandData& -- a reference to a command data.
 */
void Lexer::assignCommandWithPlaceHolder(CommandData* command) {
    // Local Variables
    CommandDataQueue queue;

    // push placeHolder into a queue WITHOUT the IF command
    try {
        pushFromVectorToQueue(m_placeHolder[m_readToPlaceHolder], queue);
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }

    // assign command with it
    command->setCommandsQueue(queue);

    // delete the placeHolder, since it was assigned
    m_placeHolder.erase(m_placeHolder.begin() + m_readToPlaceHolder);

    // --indexer
    m_readToPlaceHolder--;
}

/**
 * createNewPlaceHolder().
 */
void Lexer::createNewPlaceHolder() {
    m_readToPlaceHolder++; // increase counter
    m_placeHolder.emplace_back(CommandDataVector()); // emplace new vector
    m_curlyBracketsFound = false; // reinitialzie to false
}