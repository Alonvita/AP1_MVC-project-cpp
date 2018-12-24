//
// Created by alon on 24/12/18.
//

#include "ConnectToServerTask.h"
#include "ConnectToServerCommand.h"

/**
 * run().
 */
bool ConnectToServerTask::run() {
    if(!m_serverRunningStatus)
        throw std::runtime_error("Server is not running yet. Make sure to run it first\n");

    auto connectToServCommand = new ConnectToServerCommand();

    // execute command
    connectToServCommand->execute(m_client, m_commandDataQueue.front(), nullptr, nullptr);

    // pop from queue
    SAFELY_POP_COMMAND_DATA_QUEUE(m_commandDataQueue);
    delete(connectToServCommand); // delete command

    return true;
}