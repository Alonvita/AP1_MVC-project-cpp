//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
#define AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H


#include "Command.h"
#include "../File_Parsing/Variables/Variable.h"

/**
 * CreateVariableCommand.
 *  Will create a Variable, given a command to set the variable with.
 */
class CreateVariableCommand : public Command {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ---------
    CreateVariableCommand(smart_ptr<Command> cmd) : cmd(cmd) {};
    ~CreateVariableCommand() = default;

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    void execute() {
        // create a new smartPtr for a new Variable with the given command
        smart_ptr<Variable> smartPtr(new Variable(cmd));
        this->variable = smartPtr;
    };

private:
    smart_ptr<Command> cmd;
    smart_ptr<Variable> variable = nullptr;
};


#endif //AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
