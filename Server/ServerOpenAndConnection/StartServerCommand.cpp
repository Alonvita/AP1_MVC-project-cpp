//
// Created by alon on 24/12/18.
//

#include "StartServerCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* inHolder).
 *
 * BindCommand.
 *
 * @param sender IClient* -- a pointer to the sending client.
 * @param commandPtr CommandData* -- a pointer to a commandData.
 * @param inHolder VarData* -- unused.
 * @param outHolder VarData* -- unused.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult StartServerCommand::execute(IClient *sender, CommandData *commandPtr, VarData *inHolder,
                                          VarData *outHolder) {
    return CommandResult(false, EXECUTION_FAILURE, "GO AWAY!\n", true);
}