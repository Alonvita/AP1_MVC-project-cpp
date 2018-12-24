//
// Created by alon on 10/12/18.
//

#include "WhileLoopCommand.h"

/**
 * execute(IClient* sender, CommandData* command, void* placeHolder).
 *
 * CommandData:
 *      name -- WHILE_LOOP_COMMAND_STR
 *      data -- the while condition
 *      Queue -- the queue will hold the command to execute while condition is met.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult WhileLoopCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    // Local Variables
    auto conditionPlaceHolder = new VarData();

    // initialization with the first while condition check
    CommandResult conditionExecuteRetVal =
            m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, commandPtr, inHolder, conditionPlaceHolder);

    if(!conditionExecuteRetVal.commandSucceeded())
        return conditionExecuteRetVal;

    // while condition is true
    while(*(bool*)(conditionPlaceHolder->get_data())) {
        // get the queue of commands for this while command
        CommandResult result = m_controller->executeCommand(commandPtr->getQueue(), sender);

        // pass inHolder's data on
        *outHolder = *inHolder;
        delete(conditionPlaceHolder);

        if(!result.commandSucceeded()) {
            return CommandResult(false, EXECUTION_FAILURE, "While Loop: " + result.getData(), true);
        }

        // recheck condition
        conditionExecuteRetVal = m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, commandPtr, inHolder, conditionPlaceHolder);

        if(!conditionExecuteRetVal.commandSucceeded())
            return CommandResult(false, EXECUTION_FAILURE, "While Loop: " + conditionExecuteRetVal.getData(), true);
    }

    // pass inHolder's data on
    *outHolder = *inHolder;

    // Everything went well -> return a successful result
    CommandResult result(true, LOOP_ENDS, "While loop ended successfully\n", true);

    delete(conditionPlaceHolder);

    return result;
}