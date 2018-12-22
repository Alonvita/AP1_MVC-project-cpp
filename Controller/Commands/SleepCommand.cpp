//
// Created by alon on 11/12/18.
//

#include "SleepCommand.h"

/**
     * execute(IClient* sender, const std::string& command, void* placeHolder).
     *
     * @param sender IClient* -- a pointer to the sending cliend.
     * @param command const std::string& -- a constant reference to a string representing the command.
     * @param placeHolder var_data* -- a placeholder.
     *
     * @return a command result, depending on the specific executed command and it's success/failure.
     */
CommandResult SleepCommand::execute(IClient* sender, CommandData command, VarData* placeHolder)  {
    try {
        int milliseconds = stoi(command.getData());

        if(milliseconds < 0) {
            throw std::runtime_error("Cannot sleep for negative value: " + command.getData());
        } else {
            sleep((unsigned int)milliseconds);
        }

        std::stringstream ss;
        ss << "Program slept for: " << command.getData() << " milliseconds\n";

        return CommandResult(true, SLEEP, ss.str(), true);

    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}