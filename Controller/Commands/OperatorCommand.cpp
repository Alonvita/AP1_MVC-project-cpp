//
// Created by alon on 09/12/18.
//

#include "OperatorCommand.h"

/**
 * Default destructor.
 */

OperatorCommand::~OperatorCommand() { this->m_opHandler = nullptr; }

/**
 * execute(IClient* sender, CommandData* command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command CommandData* -- a point to a command data.
 * @param placeHolder VarData* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult OperatorCommand::execute(IClient* sender, CommandData* command, VarData* placeHolder) {
    //try to evaluate
    try {
        // TODO: add a mutex lock here

        // evaluate the operation containing LHS OP RHS
        bool result = this->m_opHandler->evaluate_operation(command->getData());

        // set into the place holder
        placeHolder->set_data(&result, BOOL);

        // return CommandResult
        std::stringstream ss;
        ss << "Successfully evaluated the expression: " << command->getData() << "\n";

        // TODO: add a mutex unlock here

        return CommandResult(true, OPERATION, ss.str(), true);
    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}

