//
// Created by alon on 10/12/18.
//

#include "AssignExistingVarCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * AssignExistingVarCommand receives a variable name as a string command, and a value to assign the variable
 *  to inside the inHolder. should inHolder not be assigned, an exception will be thrown.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult AssignExistingVarCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(inHolder->get_type() == NOT_ASSIGNED) {
        std::stringstream ss;
        ss << "There was no value to assign var named: " << commandPtr->getData() << ", to...\n";

        return CommandResult(false, EXECUTION_FAILURE, ss.str(), true);
    }

    try {

        // set an existing var with the created double
        this->m_vMapContainer->setExistingVar(commandPtr->getData(), *inHolder);

        std::stringstream ss;
        ss << "Variable: \"" << commandPtr->getData() << "\" was successfully assigned.\n";

        // pass inHolder on.
        *outHolder = *inHolder;

        return CommandResult(true, ASSIGN_VAR, ss.str(), true);
    } catch(std::exception& e) {
        // and return a EXECUTION_FAILURE commandPtr result.
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}