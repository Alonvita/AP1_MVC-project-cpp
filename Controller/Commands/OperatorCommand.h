//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H
#define AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H


#include "ICommand.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

class OperatorCommand : ICommand {
    OperatorCommand(MathExpressionsHandler* handler) : m_handler(handler) {};
    ~OperatorCommand() { this->m_handler = nullptr; };

    /**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder coid* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
    CommandResult execute(IClient* sender, const std::string& command, var_data* placeHolder) override;

private:
    MathExpressionsHandler* m_handler;
};


#endif //AP1_SEMETSER_PROJECT_OPERATORCOMMAND_H
