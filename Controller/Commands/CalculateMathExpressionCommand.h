//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H
#define AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H


#include "ICommand.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

class CalculateMathExpressionCommand : public ICommand {
public:
    CalculateMathExpressionCommand(MathExpressionsHandler* handler) : m_mathExpressionsHandler(handler) {};
    ~CalculateMathExpressionCommand() { this->m_mathExpressionsHandler = nullptr; }

    CommandResult execute(IClient* sender, CommandData command, VarData* placeHolder) override;

private:
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CALCULATEMATHEXPRESSIONCOMMAND_H
