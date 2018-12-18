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
    for(auto it = strList.begin(); it != strList.end(); ++it) {
        LexerStringEvaluationResult evaluationResult = evaluateString(*it);

        try {
            resultBasedExecution(evaluationResult, strList, it, outQueue);
        } catch(std::exception& e) {
            throw e;
        }
    }

    return outQueue;
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
/**
 * resultBasedExecution(LexerStringEvaluationResult result,
                                 ConstStringRef command, StringsPairQueue outQueue).
 *
 * @param result LexerStringEvaluationResult -- enum
 * @param it StringsList::iterator& -- iterator to a strings list.
 * @param outQueue StringsPairQueue -- a queue to push the result to.
 */
void Lexer::resultBasedExecution(LexerStringEvaluationResult result,  StringsList strList,
                                 StringsList::iterator &it, StringsPairQueue& outQueue) {
    switch(result) {
        case LEXER_PARSE_SERVER_OPEN: {
            try {
                openServer(it);
            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        case LEXER_PARSE_BIND_TO: {
            try {
                parseBindCommand(it, outQueue);
            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        case LEXER_PARSE_CREATE_VARIABLE: {
            try {
                parseCreateVar(strList, it, outQueue);
            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        case LEXER_PARSE_CONNECT_CLIENT_TO_SERVER: {
            try {
                connectClientToServer(it);
            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        case LEXER_PARSE_PRINT: {
            try {

            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        case LEXER_PARSE_START_WHILE_LOOP: {
            try {

            } catch (std::exception& e) {
                throw e;
            }
            break;
        }

        // Unknown command -> return failures
        default: {
            std::stringstream ss;
            ss << "Failed trying to parse unknown command: ";
            ss << (*it) << "\n";

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
void Lexer::connectClientToServer(StringsList::iterator &it) {
    if(this->m_client->isConnected())
        throw std::runtime_error("This client is already connected to a sever\n");

    try {
        // advance it and then get the IP Address
        std::string ip_address = *++it;

        // get the port number
        std::string port = *it++;

        // try to connect to the server
        this->m_client->connectToServer(stoi(port), ip_address);
    } catch(std::exception& e) {
        throw e;
    }
}

/**
 * parseBindCommand(StringsList::iterator &it, StringsPairQueue outqueue).
 *
 * @param it StringsList::iterator & -- a reference to a stringsList iterator.
 * @param outQueue StringsPairQueue & -- a strings of pair queue to insert the result to.
 */
void Lexer::parseBindCommand(StringsList::iterator &it, StringsPairQueue& outQueue) {
    StringsPair bindCommandAndData;

    // operation:
    //  1). take string [string "bind"] and advance iterator.
    //  2). take string [expected file path as data] and advance iterator.
    //
    //  iterator is expected to point list.end() after this.
    bindCommandAndData = std::make_pair((*it++), (*it++));

    // push it to the queue
    outQueue.push(bindCommandAndData);
}

/**
 * parseCreateVar(StringsList::iterator &it, StringsPairQueue &outQueue).
 *
 * @param strList const StringsList& strList -- a const ref to a StringsList
 * @param it StringsList::iterator & -- a reference to a stringsList iterator.
 * @param outQueue StringsPairQueue & -- a strings of pair queue to insert the result to.
 */
void Lexer::parseCreateVar(const StringsList& strList,
                           StringsList::iterator &it, StringsPairQueue &outQueue) {
    StringsPair varCommandAndData;

    varCommandAndData = std::make_pair((*it++), (*it++));

    // iterator is expected to point "=" now.
    // we will need to call parseLine again AFTER advancing the iterator,
    //  and flushing the rest of the queue into a string..
    StringsPairQueue data = parseLine(flushIteratorsContentToString(strList, ++it));

    // push the data to the queue.
    while(!data.empty()) {
        outQueue.push(data.front());
        data.pop();
    }
}

// TODO: fileLinesToQueue()
// TODO: will open a file and call parseLine over the lines to create a queue of it's own.

/// ------ UTILITY ------
/**
 * flushIteratorsContentToString(const StringsList& strList, StringsList::iterator &it).
 *
 * @param strList const StringsList& -- a constant reference to a StringsList
 * @param it StringsList::iterator& -- a reference to a StringsList's iterator
 *
 * @return a string holding the rest of the list's strings separated by " "
 */
std::string Lexer::flushIteratorsContentToString(const StringsList& strList, StringsList::iterator &it) {
   std::stringstream ss;

   while(it != strList.end()) {
       ss << (*it) << " ";
       ++it;
   }

   return ss.str();
}