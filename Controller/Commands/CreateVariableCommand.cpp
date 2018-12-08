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
CommandResult CreateVariableCommand::execute(IClient *sender, const std::string &command, void *placeHolder) {
    std::ostringstream returnMessage;

    // bad location for placeHolder or nullptr received
    if (placeHolder == nullptr) {
        returnMessage << "placeHolder is nullptr..." << "\n";

        return CommandResult(true, UNDEFINED, returnMessage.str(), true);
    }
    
    try {

        // try to cast the placeHolder to a type double
        double value = *((double *) placeHolder);

        // add it to the map
        this->m_parser->addToMap(command, value);

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