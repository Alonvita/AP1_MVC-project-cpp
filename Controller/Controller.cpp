//
// Created by alon on 07/12/18.
//

#include "Controller.h"

/**
 *
 * @param command
 * @param client
 * @return
 */
CommandResult Controller::executeCommand(const std::string& command, int client) {
    // find command in map
    auto it = commandsList.find(command);

    // if not contains
    if (it == commandsList.end())
        return CommandResult(false, UNDEFINED, "Unknown Command\n", true); // return unknown command

    return (*it).second->execute(nullptr, "nada");
}