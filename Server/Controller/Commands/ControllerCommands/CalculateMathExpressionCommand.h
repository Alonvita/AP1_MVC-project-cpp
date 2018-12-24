//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H
#define AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H

#include "IControllerCommand.h"
#include "../../Math_Expressions_Handling/MathExpressionsHandler.h"

class CalculateMathExpressionCommand : public IControllerCommand {
public:
    CalculateMathExpressionCommand(MathExpressionsHandler* handler) : m_mathExpressionsHandler(handler) {};
    ~CalculateMathExpressionCommand() { this->m_mathExpressionsHandler = nullptr; }

    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;

private:
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H
