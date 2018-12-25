//
// Created by alon on 23/12/18.
//

#include "ClientHandler.h"

/**
 * run().
 */
void ClientHandler::run() {
    ssize_t n;
    char msg[MAX_PACKET_SIZE];

    while(m_client->isConnected()) {
        // read from command line
        if(fgets(msg, MAX_PACKET_SIZE, stdin) == 0) {
            m_client->disconnect(false);
            return;
        }

        CommandDataQueue commandsQueue; // local variable

        // parse the line from lexer
        m_lexer->parseLine(msg, commandsQueue);

        // check if lexer is still reading a section.
        //  If so, continue to the next iteration instead of executing.
        if(!m_lexer->doneReadingSection())
            continue;

        // execute given commands
        m_result = m_controller->executeCommand(commandsQueue, m_client);

        // send command result to client
        m_client->receiveCommandResult(m_result);
    }

    // notifies the other end of the server that the client has finished it's operation
    m_lock.getCondVariable().notify_one();
}