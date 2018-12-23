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

    // TODO: check if command and use Util if it works properly.

    // Local Variables
    auto condition = new VarData();

    // initialization with the first while condition check
    CommandResult retVal =
            m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, commandPtr, inHolder, condition);

    if(!retVal.commandSucceeded())
        return retVal;

    // while condition is true
    while(*(bool*)(condition->get_data())) {
        // get the queue of commands for this while command
        CommandDataQueue whileQueue = commandPtr->getQueue();

        // Execute all commands
        while(!whileQueue.empty()) {
            CommandData* commandToExecute = whileQueue.front(); // get next command to execute
            whileQueue.pop(); // pop the command from the queue

            // Local Variables
            m_placeHoldersContainer.push_back(new VarData());
            m_placeHoldersCount++;

            // Local Vairables
            VarData* currPH = m_placeHoldersContainer[m_placeHoldersCount];
            VarData* lastPH = m_placeHoldersContainer[m_placeHoldersCount - 1];

            auto map_it = this->m_commandsList->find(commandToExecute->getName());

            if(map_it == this->m_commandsList->end()) {
                delete(condition);
                return CommandResult(true, UNDEFINED, "Unknown command given inside while loop\n", true);
            }

            retVal = (*map_it).second->execute(sender, commandToExecute, lastPH, currPH);

            // command executed poorly -> return
            if(!retVal.commandSucceeded()) {
                delete(condition);
                return retVal;
            }
        }

        // delete and assign with new
        delete(condition);
        condition = new VarData();

        // if it's a loop -> recheck condition
        retVal =
                this->m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, commandPtr, inHolder, condition);

        // command executed poorly -> return
        if(!retVal.commandSucceeded()) {
            delete(condition);
            return retVal;
        }
    }

    // pass inHolder's data on
    *outHolder = *inHolder;

    // Everything went well -> return a successful result
    CommandResult result(true, LOOP_ENDS, "While loop ended successfully\n", true);

    delete(condition);

    return result;
}