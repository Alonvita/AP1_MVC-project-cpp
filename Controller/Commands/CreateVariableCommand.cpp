//
// Created by alon on 04/12/18.
//

#include "CreateVariableCommand.h"

/**
 * execute(IClient* sender, CommandData* command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param command CommandData* -- a point to a command data.
 * @param placeHolder VarData* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult CreateVariableCommand::execute(IClient *sender, CommandData* command, VarData* placeHolder) {
    std::ostringstream returnMessage;

    // TODO: can add the value to placeholder so the programm supports expressions such as:
    // TODO:    var a = var b = 15

    // bad location for placeHolder or nullptr received
    if (placeHolder == nullptr) {
        returnMessage << "placeHolder is nullptr..." << "\n";

        return CommandResult(false, UNDEFINED, returnMessage.str(), true);
    }
    
    try {
        // add it to the map
        this->m_vContainer->addToMap(command->getData(), placeHolder);

        // create the message
        returnMessage << "SUCCESS: creating new variable: " << command->getData() << "\n";

        return CommandResult(true, CREATE_VAR, returnMessage.str(), true);
    } catch (std::bad_cast &e) {
        return CommandResult(false, EXECUTION_FAILURE, "BAD_CAST: could not cast to a double from placeHolder\n", true);
    } catch (std::exception &e) {
        returnMessage << "FAILURE when adding " << command->getData() << " to the map\n";

        return CommandResult(false, EXECUTION_FAILURE, returnMessage.str(), true);
    }

}