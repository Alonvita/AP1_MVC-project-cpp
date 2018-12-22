//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H
#define AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H


#include <map>
#include "ICommand.h"
#include "../../DefinesAndTypedefs.h"

class WhileLoopCommand : public ICommand {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    explicit WhileLoopCommand(CommandsMap* commandsList) : m_commandsList(commandsList) {};
    ~WhileLoopCommand() override {
        this->m_commandsList = nullptr;

        for(VarData* vD : this->m_placeHoldersContainer)
            delete(vD);
    };

    /// ---------- EXECUTION ----------
    CommandResult execute(IClient* sender, CommandData command, VarData* placeHolder) override;

private:
    CommandsMap* m_commandsList;
    unsigned long m_placeHoldersCount = 0;
    std::vector<VarData*> m_placeHoldersContainer;
};


#endif //AP1_SEMETSER_PROJECT_WHILELOOPCOMMAND_H
