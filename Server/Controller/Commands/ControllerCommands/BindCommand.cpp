//
// Created by alon on 09/12/18.
//

#include "BindCommand.h"

/**
 * Default Destructor.
 */
BindCommand::~BindCommand() = default;

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * BindCommand.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult BindCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    // create a new VarData to be held inside inHolder
    const char* filePath = commandPtr->getData().c_str();

    // get the file path
    try {
        int fp = open(filePath, O_RDWR);

        if(fp == -1) {
            throw std::runtime_error("Could not find file path to: " + std::string(filePath));
        }


        // set type and data to outHolder
        outHolder->set_data(&fp, BIND);

        std::stringstream returnMessage;
        returnMessage << "Bind Successful" << "\n";

        return CommandResult(true, BIND_COMMAND, returnMessage.str(), true);
    } catch(std::ios_base::failure& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}