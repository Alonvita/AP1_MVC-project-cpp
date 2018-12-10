//
// Created by alon on 09/12/18.
//

#include "OperatorCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending cliend.
 * @param command const std::string& -- a constant reference to a string representing the command.
 * @param placeHolder coid* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult OperatorCommand::execute(IClient* sender, ConstStringRef command, var_data* placeHolder) {
    //try to evaluate
    try {
        bool result = this->m_opHandler->evaluate_operation(command);

        // set into the place holder
        placeHolder->set_type(BOOL);
        placeHolder->set_data(&result);

        // return CommandResult
        std::stringstream ss;
        ss << "Successfully evaluated the expression: " << command << "\n";

        return CommandResult(true, OPERATION, ss.str(), true);
    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}

