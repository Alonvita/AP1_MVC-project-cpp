//
// Created by alon on 10/12/18.
//

#include "WhileLoopCommand.h"

/**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     *          WhileLoop convention is:
     *              condition (\n)
     *              command (\n)
     *              variables (\n)
     *              command (\n)
     *              variables(\n)
     *              ...
     * @param placeHolder var_data* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
CommandResult WhileLoopCommand::execute(IClient* sender, CommandData* command, VarData* placeHolder) {
    // Local Variables
    auto condition = new VarData();

    // initialization with the first while condition check
    CommandResult retVal =
            this->m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, command, condition);

    if(!retVal.commandSucceeded())
        return retVal;

    // while condition is true
    while(*(bool*)(condition->get_data())) {
        // get the queue of commands for this while command
        CommandDataQueue whileQueue = command->getQueue();

        // Execute all commands
        while(!whileQueue.empty()) {
            CommandData* commandToExecute = whileQueue.front(); // get next command to execute
            whileQueue.pop(); // pop the command from the queue

            // Local Variables
            m_placeHoldersContainer.push_back(new VarData());
            m_placeHoldersCount++;

            // Local Vairables
            VarData* lastPH = m_placeHoldersContainer[m_placeHoldersCount - 1];
            auto map_it = this->m_commandsList->find(commandToExecute->getName());

            if(map_it == this->m_commandsList->end()) {
                delete(condition);
                return CommandResult(true, UNDEFINED, "Unknown command given inside while loop\n", true);
            }

            retVal = (*map_it).second->execute(sender, commandToExecute, lastPH);

            // command executed poorly -> return
            if(!retVal.commandSucceeded()) {
                delete(condition);
                return retVal;
            }
        }

        // delete and assign with new
        delete(condition);
        condition = new VarData();

        // recheck condition
        retVal =
                this->m_commandsList->at(OPERATOR_COMMAND_STR)->execute(sender, command, condition);

        // command executed poorly -> return
        if(!retVal.commandSucceeded()) {
            delete(condition);
            return retVal;
        }
    }

    // Everything went well -> return a successful result
    CommandResult result(true, LOOP_ENDS, "While loop ended successfully\n", true);

    delete(condition);

    return result;
}