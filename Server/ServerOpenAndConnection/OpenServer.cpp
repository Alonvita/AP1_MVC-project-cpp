//
// Created by alon on 24/12/18.
//

#include "OpenServer.h"

/**
 * run().
 */
IServer* OpenServer::run() {
    CommandData* commandData = m_commandDataQueue.front();
    std::vector<std::string> dataFromCommand;

    splitStringToVector(commandData->getData(), " ", dataFromCommand, false);

    try {
        auto server =
                new TCPServer(stoi(dataFromCommand[0]), m_controller, m_lexer, stoi(dataFromCommand[1]), m_lock);

        // pop from queue
        SAFELY_POP_COMMAND_DATA_QUEUE(m_commandDataQueue);

        return server;
    } catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }

}