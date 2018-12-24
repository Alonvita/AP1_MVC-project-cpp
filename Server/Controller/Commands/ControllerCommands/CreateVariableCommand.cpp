//
// Created by alon on 04/12/18.
//

#include "CreateVariableCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult CreateVariableCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    std::ostringstream returnMessage;
    
    try {
        // add an empty var to map
        this->m_vContainer->addToMap(commandPtr->getData(), new VarData());

        // create the message
        returnMessage << "SUCCESS: creating new variable: " << commandPtr->getData() << "\n";

        // pass inHolder on
        *outHolder = *inHolder;

        return CommandResult(true, CREATE_VAR, returnMessage.str(), true);
    } catch (std::bad_cast &e) {
        return CommandResult(false, EXECUTION_FAILURE, "BAD_CAST: could not cast to a double from placeHolder\n", true);
    } catch (std::exception &e) {
        returnMessage << "FAILURE when adding " << commandPtr->getData() << " to the map\n";

        return CommandResult(false, EXECUTION_FAILURE, returnMessage.str(), true);
    }

}