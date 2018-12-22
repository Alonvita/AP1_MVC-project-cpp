//
// Created by alon on 09/12/18.
//

#include "OperatorCommand.h"

/**
 * Default destructor.
 */

OperatorCommand::~OperatorCommand() { this->m_opHandler = nullptr; }

/**
 * execute(IClient* sender, const std::string& command, void* placeHolder).
 *
 * READ BEFORE USING:
 *  The OperatorCommand receives a double inside the varData as LHS to the operator. then, the command string
 *   received will hold [OPERATOR] [RHS]. This is used to support math expressions in both LHS and RHS for expressions
 *
 *   such as: altitude + 150 < altimeter_max_value / 2
 *
 *   Therefore, this first thing that the execution does, is to create a string containing LHS OP RHS.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command const std::string& -- a constant reference to a string representing the command.
 * @param placeHolder VarData* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult OperatorCommand::execute(IClient* sender, ConstStringRef command, VarData* placeHolder) {
    if(placeHolder->get_type() != DOUBLE) {
        std::stringstream errorString;

        errorString << "Cannot execute operator command when lhs is not a valuated expression (type double)\n";

        return CommandResult(false, EXECUTION_FAILURE, errorString.str(), true);
    }

    //try to evaluate
    try {
        // TODO: add a mutex lock here

        // Local Variable
        std::stringstream ss;

        // get LHS data
        ss << placeHolder->get_data() << " "; // data is of type double
        ss << command;

        // evaluate the operation containing LHS OP RHS
        bool result = this->m_opHandler->evaluate_operation(ss.str());

        // set into the place holder
        placeHolder->set_data(&result, BOOL);

        // reinitialize ss to an empty string
        ss.str("");

        // return CommandResult
        ss << "Successfully evaluated the expression: " << command << "\n";

        // TODO: add a mutex unlock here

        return CommandResult(true, OPERATION, ss.str(), true);
    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}

