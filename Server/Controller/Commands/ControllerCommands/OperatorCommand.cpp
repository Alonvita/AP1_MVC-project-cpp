//
// Created by alon on 09/12/18.
//

#include "OperatorCommand.h"

/**
 * Default destructor.
 */

OperatorCommand::~OperatorCommand() { this->m_opHandler = nullptr; }

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult OperatorCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    //try to evaluate
    try {
        // TODO: add a mutex lock here

        // evaluate the operation containing LHS OP RHS
        bool* result = (bool*) malloc(sizeof(bool));

        *result = this->m_opHandler->evaluate_operation(commandPtr->getData());

        // set into the out holder
        outHolder->set_data(result, BOOL);

        free(result);

        // return CommandResult
        std::stringstream ss;
        ss << "Successfully evaluated the expression: " << commandPtr->getData() << "\n";

        // TODO: add a mutex unlock here

        return CommandResult(true, OPERATION, ss.str(), true);
    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}

