//
// Created by alon on 09/12/18.
//

#include "OperatorCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending cliend.
 * @param command const std::string& -- a constant reference to a string representing the command.
 * @param placeHolder coid* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult execute(IClient* sender, const std::string& command, var_data* placeHolder) {

}