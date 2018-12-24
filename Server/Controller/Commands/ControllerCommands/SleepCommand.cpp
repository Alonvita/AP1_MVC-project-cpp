//
// Created by alon on 11/12/18.
//

#include "SleepCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder var_data* -- a inHolder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult SleepCommand::execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) {
    if(sender == nullptr)
        throw std::runtime_error("Client is nullptr, and may not be connected to any server\n");

    try {
        double milliseconds = SECONDS_TO_MILLISECONDS(stod(commandPtr->getData()));

        if(milliseconds < 0) {
            throw std::runtime_error("Cannot sleep for negative value: " + commandPtr->getData());
        } else {
            sleep(milliseconds);
        }

        std::stringstream ss;
        ss << "Program slept for: " << commandPtr->getData() << " milliseconds\n";

        // pass inHolder's data on.
        *outHolder = *inHolder;

        return CommandResult(true, SLEEP, ss.str(), true);

    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}