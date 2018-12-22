//
// Created by alon on 22/12/18.
//

#include "CommandsUtil.h"

CommandResult executeCommandsQueue(IClient* sender, CommandDataQueue& whileQueue,
                                   std::vector<VarData*>& m_placeHoldersContainer,
                                   unsigned long& m_placeHoldersCount, VarData* condition,
                                   CommandResult& retVal, CommandsMap* m_commandsList) {
    // Execute all commands
    while(!whileQueue.empty()) {
        CommandData* commandToExecute = whileQueue.front(); // get next command to execute
        whileQueue.pop(); // pop the command from the queue

        // Local Variables
        m_placeHoldersContainer.push_back(new VarData());
        m_placeHoldersCount++;

        // Local Vairables
        VarData* lastPH = m_placeHoldersContainer[m_placeHoldersCount - 1];
        auto map_it = m_commandsList->find(commandToExecute->getName());

        if(map_it == m_commandsList->end()) {
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
}