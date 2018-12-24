//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H
#define AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H


#include <map>
#include "../../IController.h"
#include "IControllerCommand.h"
#include "../../../../DefinesAndTypedefs.h"

class WhileLoopCommand : public IControllerCommand {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    WhileLoopCommand(IController* controller, ControllerCommandsMap* commandsList) :
                m_controller(controller), m_commandsList(commandsList) {};
    ~WhileLoopCommand() override {
        this->m_commandsList = nullptr;

        for(VarData* vD : this->m_placeHoldersContainer)
            delete(vD);
    };

    /// ---------- EXECUTION ----------
    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;

private:
    IController* m_controller;
    ControllerCommandsMap* m_commandsList;
    unsigned long m_placeHoldersCount = 0;
    std::vector<VarData*> m_placeHoldersContainer;
};


#endif //AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H
