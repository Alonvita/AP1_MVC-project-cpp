//
// Created by alon on 10/12/18.
//

#include "CalculateMathExpressionCommand.h"

/**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder var_data* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
CommandResult CalculateMathExpressionCommand::execute(IClient* sender, CommandData* command, VarData* placeHolder) {
    // try to evaluate math expression, or catch the exception thrown
    try {
        double valResult = this->m_mathExpressionsHandler->parse_mathematical_expression(command->getData());

        placeHolder->set_data(&valResult, DOUBLE);
    } catch(std::exception& e) {
        // return a failure result with the caught exception
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }


    return CommandResult(true, CALCULATE_EXPRESSION, "Math expression calculation successful\n", true);
}