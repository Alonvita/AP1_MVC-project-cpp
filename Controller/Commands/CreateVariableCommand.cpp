//
// Created by alon on 04/12/18.
//

#include "CreateVariableCommand.h"

/**
 *
 * @param sender
 * @param command
 * @param placeHolder
 * @return
 */
CommandResult CreateVariableCommand::execute(IClient *sender, ConstStringRef command, var_data* placeHolder) {
    std::ostringstream returnMessage;

    // bad location for placeHolder or nullptr received
    if (placeHolder == nullptr) {
        returnMessage << "placeHolder is nullptr..." << "\n";

        return CommandResult(false, UNDEFINED, returnMessage.str(), true);
    }
    
    try {
        // add it to the map
        this->m_vContainer->addToMap(command, placeHolder);

        // create the message
        returnMessage << "SUCCESS: creating new variable: " << command << "\n";

        return CommandResult(true, CREATE_VAR, returnMessage.str(), true);
    } catch (std::bad_cast &e) {
        return CommandResult(false, EXECUTION_FAILURE, "BAD_CAST: could not cast to a double from placeHolder\n", true);
    } catch (std::exception &e) {
        returnMessage << "FAILURE when adding " << command << " to the map\n";

        return CommandResult(false, EXECUTION_FAILURE, returnMessage.str(), true);
    }

}