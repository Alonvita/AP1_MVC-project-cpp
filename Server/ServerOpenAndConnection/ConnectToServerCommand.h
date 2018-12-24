//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONNECTTOSERVERCOMMAND_H
#define AP1_SEMETSER_PROJECT_CONNECTTOSERVERCOMMAND_H

#include "IServerHandlingCommand.h"

class ConnectToServerCommand : public IServerHandlingCommand {
public:
    ConnectToServerCommand() = default;

    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;
};


#endif //AP1_SEMETSER_PROJECT_CONNECTTOSERVERCOMMAND_H
