//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_COMMAND_H
#define AP1_SEMETSER_PROJECT_COMMAND_H

#include <queue>
#include <iostream>

#include "../../View/IClient.h"

/**
 * Command will serve as a pure-virtual class for commands to inherit.
 *  Commands must be able to execute().
 */

class ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    ICommand() = default;
    ~ICommand() = default;

    /// ---------- PURE VIRTUAL METHODS ----------
    /**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder coid* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
    virtual CommandResult execute(IClient* sender, const std::string& command, void* placeHolder) = 0;
};

#endif //AP1_SEMETSER_PROJECT_COMMAND_H
