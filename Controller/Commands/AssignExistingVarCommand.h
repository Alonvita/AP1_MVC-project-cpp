//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ASSIGNEXISTINGVARCOMMAND_H
#define AP1_SEMETSER_PROJECT_ASSIGNEXISTINGVARCOMMAND_H


#include "ICommand.h"
#include "../VariablesMapContainer.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

class AssignExistingVarCommand : public ICommand {
public:
    ~AssignExistingVarCommand() override { this->m_mathExpressionsHandler = nullptr; this->m_vMapContainer = nullptr; }

    explicit AssignExistingVarCommand(VariablesMapContainer* vMapContainer, MathExpressionsHandler* handler) :
            m_vMapContainer(vMapContainer), m_mathExpressionsHandler(handler) {};

    CommandResult execute(IClient* sender, CommandData* command, VarData* placeHolder) override;

private:
    VariablesMapContainer* m_vMapContainer;
    MathExpressionsHandler* m_mathExpressionsHandler;

};


#endif //AP1_SEMETSER_PROJECT_ASSIGNEXISTINGVARCOMMAND_H
