//
// Created by alon on 22/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_IFCOMMAND_H
#define AP1_SEMETSER_PROJECT_IFCOMMAND_H


#include "../../IController.h"
#include "IControllerCommand.h"

class IfCommand : public IControllerCommand {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    explicit IfCommand(IController* controller, ControllerCommandsMap* map) :
                m_commandsList(map), m_controller(controller) {};
    ~IfCommand() override = default;

    /// ---------- EXECUTION ----------
    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;

private:
    IController* m_controller;
    ControllerCommandsMap* m_commandsList;
};


#endif //AP1_SEMETSER_PROJECT_IFCOMMAND_H
