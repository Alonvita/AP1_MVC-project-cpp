//
// Created by alon on 24/12/18.
//

#include "OpenServer.h"
#include "StartServerCommand.h"

/**
 * run().
 */
IServer* OpenServerTask::run() {
    // start a new Server Command
    auto startServerCommand = new StartServerCommand(m_controller);

    // TODO: open the server

    // pop from queue
    SAFELY_POP_COMMAND_DATA_QUEUE(m_commandDataQueue);
    delete(startServerCommand); // delete command
}