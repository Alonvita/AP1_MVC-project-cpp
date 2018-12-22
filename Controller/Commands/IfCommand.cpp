//
// Created by alon on 22/12/18.
//

#include "IfCommand.h"

/**
 * execute(IClient* sender, CommandData* command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command CommandData* -- a point to a command data.
 * @param placeHolder VarData* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult IfCommand::execute(IClient *sender, CommandData *command, VarData *placeHolder) {
    // Local Variables
    auto condition = new VarData();

    // initialization with the first while condition check
    CommandResult retVal =
            this->m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, command, condition);

    if(!retVal.commandSucceeded())
        return retVal;

    // while condition is true
    if(*(bool*)(condition->get_data())) {
        // get the queue of commands for this while command
        CommandDataQueue whileQueue = command->getQueue();
        CommandResult result = executeCommandsQueue(sender,
                                    whileQueue,
                                    m_placeHoldersContainer,
                                    m_placeHoldersCount,
                                    condition,
                                    retVal,
                                    m_commandsList);

        if(result.commandSucceeded()) {
            return CommandResult(true, IF_END, "If command ended successfully - condition was met\n", true);
        } else {
            return CommandResult(false, EXECUTION_FAILURE, result.getData(), true);
        }
    }

    // Everything went well -> return a successful result
    return CommandResult(true, IF_END, "If command ended successfully - condition was NOT met\n", true);
}