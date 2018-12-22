//
// Created by alon on 22/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_IFCOMMAND_H
#define AP1_SEMETSER_PROJECT_IFCOMMAND_H


#include "ICommand.h"
#include "CommandsUtil/CommandsUtil.h"

class IfCommand : ICommand {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    explicit IfCommand(CommandsMap* commandsList) : m_commandsList(commandsList) {};
    ~IfCommand() override {
        this->m_commandsList = nullptr;

        for(VarData* vD : this->m_placeHoldersContainer)
            delete(vD);
    };

    /// ---------- EXECUTION ----------
    CommandResult execute(IClient* sender, CommandData* command, VarData* placeHolder) override;

private:
    CommandsMap* m_commandsList;
    unsigned long m_placeHoldersCount = 0;
    std::vector<VarData*> m_placeHoldersContainer;
};


#endif //AP1_SEMETSER_PROJECT_IFCOMMAND_H
