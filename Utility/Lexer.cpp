//
// Created by alon on 11/12/18.
//

#include "Lexer.h"

/**
 * parseLine(const std::string &line).
 *
 * @param line ConstStringRef -- a constant reference to a string.
 *
 * @return a queue of string pairs holding [command (string)] [variables (string)] per pair.
 */
StringsPairQueue Lexer::parseLine(ConstStringRef line) {
    StringsList strList;
    StringsPairQueue outQueue = StringsPairQueue();

    splitStringToList(line, " ", strList, false);

    // evaluate every string in the list, and execute accordingly
    for(ConstStringRef str : strList) {
        LexerStringEvaluationResult evaluationResult = evaluateString(str);

        try {
            resultBasedExecution();
        } catch(std::exception& e) {
            throw e;
        }
    }
}

/**
 * evaluateString(ConstStringRef str).
 *
 * @param str ConstStringRef -- a const reference to a string.
 *
 * @return an enumerator representing the type of the string received.
 */
LexerStringEvaluationResult Lexer::evaluateString(ConstStringRef str) {
    if(str == RAW_OPEN_SERVER_STR)
        return LEXER_PARSE_SERVER_OPEN;

    if(str == RAW_BIND_STR)
        return LEXER_PARSE_BIND_TO;

    if(str == RAW_CREATE_VARIABLE_STR)
        return LEXER_PARSE_CREATE_VARIABLE;

    if(str == RAW_CONNECT_TO_SEVER_STR)
        return LEXER_PARSE_CONNECT_CLIENT_TO_SERVER;

    if(str == RAW_PRINT_STR)
        return LEXER_PARSE_PRINT;

    if(str == RAW_WHILE_LOOP_STR)
        return LEXER_PARSE_START_WHILE_LOOP;

    return LEXER_PARSE_UNKNOWN_STR;

}

/// ---------- COMMANDS EXECUTION ----------

void Lexer::resultBasedExecution(LexerStringEvaluationResult result, ConstStringRef command) {
    switch(result) {
        case LEXER_PARSE_SERVER_OPEN: {
            break;
        }

        case LEXER_PARSE_BIND_TO: {
            break;
        }

        case LEXER_PARSE_CREATE_VARIABLE: {
            break;
        }

        case LEXER_PARSE_CONNECT_CLIENT_TO_SERVER: {
            break;
        }

        case LEXER_PARSE_PRINT: {
            break;
        }

        case LEXER_PARSE_START_WHILE_LOOP: {
            break;
        }

        // Unknown command -> return failures
        default: {
            std::stringstream ss;
            ss << "Failed trying to parse unknown command: ";
            ss << command << "\n";

            throw std::runtime_error(ss.str());
        }
    }
}

/**
 * flushOpenServerCommand(StringsList::iterator &it).
 *
 * @param it StringsList::iterator -- an iterator to a StringsList.
 * @return a CommandResult
 */
void Lexer::openServer(StringsList::iterator &it) {
    std::stringstream ss;

    if(this->m_serverAssigned) {
        ss << "Server is already open on port: ";
        // TODO: add this after server creation
        //ss << m_server.getPort() << "\n;

        throw std::runtime_error(ss.str());
    }
}

/**
 * connectToServer(StringsList::iterator &it).
 *
 * @param it StringsList::iterator -- an iterator to a StringsList.
 * @return a CommandResult.
 */
void Lexer::ParseConnectToServer(StringsList::iterator &it) {
    if(this->m_client->isConnected())
        throw std::runtime_error("This client is already connected to a sever\n");

    try {
        // get the IP Address
        std::string ip_address = *++it;

        // get the port number
        std::string port = *it++;

        // try to connect to the server
        this->m_client->connectToServer(stoi(port), ip_address);
    } catch(std::exception& e) {
        throw e;
    }
}

// TODO: fileLinesToQueue()
// TODO: will open a file and call parseLine over the lines to create a queue of it's own.