//
// Created by alon on 10/12/18.
//

#include "AssignExistingVarCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* placeHolder).
 *
 * AssignExistingVarCommand receives a variable name as a string command, and a value to assign the variable
 *  to inside the placeHolder. should placeHolder not be assigned, an exception will be thrown.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command const std::string& -- a constant reference to a string representing the command.
 *
 * @param placeHolder var_data* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult AssignExistingVarCommand::execute(IClient* sender, CommandData* command, VarData* placeHolder) {
    if(placeHolder->get_type() == NOT_ASSIGNED) {
        std::stringstream ss;
        ss << "There was no value to assign : " << command->getData() << " to...\n";

        return CommandResult(false, EXECUTION_FAILURE, ss.str(), true);
    }

    // Create a new double on the heap
    auto val = (double*) malloc(sizeof(double));

    try {
        // assign double with the given value
        *val = (*((double*) placeHolder->get_data()));

        // set an existing var with the created double
        this->m_vMapContainer->setExistingVar(command->getData(), val, DOUBLE);

        std::stringstream ss;
        ss << "Variable: \"" << command->getData() << "\" was assigned with : \"" << (*val);

        //clear val to prevent dangling pointers
        val = nullptr;

        return CommandResult(true, ASSIGN_VAR, ss.str(), true);
    } catch(std::exception& e) {
        // should an exception occur, we want to free val here to prevent leaks.
        free(val);

        // and return a EXECUTION_FAILURE command result.
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}