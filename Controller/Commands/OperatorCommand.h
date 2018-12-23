//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H
#define AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H


#include "ICommand.h"
#include "../Operators_Handler/OperatorsHandler.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

class OperatorCommand : public ICommand {
public:
    explicit OperatorCommand(OperatorsHandler* opHandler) : m_opHandler(opHandler) {};
    ~OperatorCommand() override;

    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;

private:
    OperatorsHandler* m_opHandler;
};


#endif //AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H
