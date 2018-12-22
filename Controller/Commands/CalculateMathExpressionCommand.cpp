//
// Created by alon on 10/12/18.
//

#include "CalculateMathExpressionCommand.h"

/**
 * execute(IClient* sender, CommandData* command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command CommandData* -- a point to a command data.
 * @param placeHolder VarData* -- a placeholder.
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