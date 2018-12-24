//
// Created by alon on 23/12/18.
//

#include "FlightGearClientHandler.h"

/**
 * run().
 */
void FlightGearClientHandler::run() {
    ssize_t n;
    char msg[MAX_PACKET_SIZE];

    while(m_client->isConnected()) {
        // receive a message
        n = recv(m_client->getSocketID(), msg, MAX_PACKET_SIZE, 0);

        // check file ended while reading
        if(n == 0) {
            m_client->disconnect(false);
            return;
        }

        CommandDataQueue commandsQueue; // local variable

        // parse the line from lexer
        m_lexer->parseLine(msg, commandsQueue);

        // execute given commands
        CommandResult result = m_controller->executeCommand(commandsQueue, m_client);

        // send command result to client
        m_client->receiveCommandResult(result);

        // clear msg
        memset(msg,'\0', MAX_PACKET_SIZE);
    }
}