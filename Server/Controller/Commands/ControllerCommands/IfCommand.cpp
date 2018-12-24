//
// Created by alon on 22/12/18.
//

#include "IfCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult IfCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    // Local Variables
    auto conditionPlaceHolder = new VarData();

    // initialization with the first while condition check
    CommandResult retVal =
            this->m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, commandPtr, inHolder, conditionPlaceHolder);

    if(!retVal.commandSucceeded())
        return retVal;

    // while condition is true
    if(*(bool*)(conditionPlaceHolder->get_data())) {
        // get the queue of commands for this while command
        CommandResult result = m_controller->executeCommand(commandPtr->getQueue(), sender);

        // pass inHolder's data on
        *outHolder = *inHolder;
        delete(conditionPlaceHolder);

        if(result.commandSucceeded()) {
            return CommandResult(true, IF_END, "If command ended successfully - condition was met\n", true);
        } else {
            return CommandResult(false, EXECUTION_FAILURE, "If Command: " + result.getData(), true);
        }
    }

    delete(conditionPlaceHolder);

    // Condition not met
    return CommandResult(true, IF_END, "If command ended successfully - condition was NOT met\n", true);
}