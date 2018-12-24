//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_STARTSERVERCOMMAND_H
#define AP1_SEMETSER_PROJECT_STARTSERVERCOMMAND_H

#include "ServerHandlingCommand.h"
#include "../Controller/Controller.h"

class StartServerCommand : public ServerHandlingCommand {
    StartServerCommand(Controller* controller) : m_controller(controller) {};

    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;

private:
    Controller* m_controller;
};


#endif //AP1_SEMETSER_PROJECT_STARTSERVERCOMMAND_H
