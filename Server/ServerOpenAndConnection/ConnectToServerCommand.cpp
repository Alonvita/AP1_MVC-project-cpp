//
// Created by alon on 24/12/18.
//

#include "ConnectToServerCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * BindCommand.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder VarData* -- unused.
 * @param outHolder VarData* -- unused.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult ConnectToServerCommand::execute(
        IClient *sender, CommandData *commandPtr, VarData *inHolder, VarData *outHolder) {
    std::vector<std::string> ipPort;

    splitStringToVector(commandPtr->getData(), " ", ipPort, false);

    try {
        uint16_t port = stoi(ipPort[1]);

        // connect client to server.
        sender->connectToServer(port, ipPort[0]);
    } catch (std::exception& e) {
        throw std::numeric_limits<short>();
    }
}