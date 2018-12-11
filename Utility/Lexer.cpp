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
CommandResult Lexer::parseLine(const std::string &line) {
    StringsList strList;
    StringsPairQueue outQueue = std::queue<std::pair<std::string, std::string>>();

    splitStringToList(line, " ", strList, true);

    for(auto it = strList.begin(); it != strList.end(); ++it) {
        // server command received
        if(openServerCommand(*it)) {
            try {
                return openServer(it);
            } catch(std::exception& e) {
                CommandResult(false, EXECUTION_FAILURE, e.what(), true);
            }
        }


        // connect command received
        if(connectCommand(*it)) {
            try {
                return ParseConnectToServer(it);
            } catch(std::exception& e) {
                CommandResult(false, EXECUTION_FAILURE, e.what(), true);
            }
        }


        // text command received
        //if(readFromFileCommand(*it))
        //      outQueue.emplace(fileLinesToQueue(*it));

        // create var command received
        //if(varCommand(*it))
            //outQueue.push(parseCreateVarCommand(it));

        // while loop command received
        //if(whileLoopCommand(*it))
            //outQueue.emplace(parseWhileLoopToQueue(it));

        throw std::runtime_error("Unknown command: " + line);
    }
}

/**
 * flushOpenServerCommand(StringsList::iterator &it).
 *
 * @param it StringsList::iterator -- an iterator to a StringsList.
 * @return a CommandResult
 */
CommandResult Lexer::openServer(StringsList::iterator &it) {
    std::stringstream ss;

    if(this->m_serverAssigned) {
        ss << "Server is already open on por: ";
        //ss << m_server.getPort() << "\n;

        return CommandResult(false, OPEN_SERVER, ss.str(), true);
    }

    ss << "server opened successfully on port: ";
    //ss << m_server.getPort() << "\n;

    return CommandResult(true, OPEN_SERVER, ss.str(), true);
}

/**
 * connectToServer(StringsList::iterator &it).
 *
 * @param it StringsList::iterator -- an iterator to a StringsList.
 * @return a CommandResult.
 */
CommandResult Lexer::ParseConnectToServer(StringsList::iterator &it) {
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
        return CommandResult(false, UNDEFINED, e.what(), true);
    }

    return CommandResult(true, CONNECTED_TO_SERVER, "Successfully connected to server\n", true);
}
// TODO: fileLinesToQueue()
// TODO: will open a file and call parseLine over the lines to create a queue of it's own.