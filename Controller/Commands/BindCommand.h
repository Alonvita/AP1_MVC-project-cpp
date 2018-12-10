//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_BINDCOMMAND_H
#define AP1_SEMETSER_PROJECT_BINDCOMMAND_H

#include <fcntl.h>
#include <sstream>

#include "ICommand.h"

class BindCommand : public ICommand {
public:
    BindCommand() = default;
    ~BindCommand() = default;

    /**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder coid* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
    CommandResult execute(IClient* sender, ConstStringRef command, VarData* placeHolder) override;
};


#endif //AP1_SEMETSER_PROJECT_BINDCOMMAND_H
