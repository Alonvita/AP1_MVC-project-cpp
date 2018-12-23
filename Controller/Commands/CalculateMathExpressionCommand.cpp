//
// Created by alon on 10/12/18.
//

#include "CalculateMathExpressionCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult CalculateMathExpressionCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    // try to evaluate math expression, or catch the exception thrown
    try {
        auto valResult = (double*) malloc(sizeof(double));

        *valResult = this->m_mathExpressionsHandler->parse_mathematical_expression(commandPtr->getData());

        outHolder->set_data(valResult, DOUBLE);

        free(valResult);
    } catch(std::exception& e) {
        // return a failure result with the caught exception
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }


    return CommandResult(true, CALCULATE_EXPRESSION, "Math expression calculation successful\n", true);
}