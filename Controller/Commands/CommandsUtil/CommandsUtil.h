//
// Created by alon on 22/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_COMMANDSUTIL_H
#define AP1_SEMETSER_PROJECT_COMMANDSUTIL_H


#include "../ICommand.h"
#include "../../../Utility/VarData.h"
#include "../../../Shared_Data/CommandData.h"
#include "../../../Shared_Data/CommandResult.h"

CommandResult executeCommandsQueue(IClient* sender, CommandDataQueue& whileQueue,
                                   std::vector<VarData*>& m_placeHoldersContainer,
                                   unsigned long& m_placeHoldersCount, VarData* condition,
                                   CommandResult& retVal, CommandsMap* m_commandsList);


#endif //AP1_SEMETSER_PROJECT_COMMANDSUTIL_H
