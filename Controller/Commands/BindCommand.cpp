//
// Created by alon on 09/12/18.
//

#include "BindCommand.h"

/**
 * Default Destructor.
 */
BindCommand::~BindCommand() = default;

/**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder coid* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
CommandResult BindCommand::execute(IClient *sender, CommandData command, VarData *placeHolder) {
    // create a new VarData to be held inside placeHolder
    const char* filePath = command.getData().c_str();

    // get the file path
    try {
        int fp = open(filePath, O_RDWR);

    // set type and data
    placeHolder->set_data(&fp, BIND);

    std::stringstream returnMessage;
    returnMessage << "Bind Successful" << "\n";

    return CommandResult(true, BIND_COMMAND, returnMessage.str(), true);
    } catch(std::ios_base::failure& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}