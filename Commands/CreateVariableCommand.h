//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
#define AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H


#include "Command.h"
#include "Variables/Variable.h"
#include "../Utilities/Reference_Counting/SmartPtr.h"

/**
 * CreateVariableCommand.
 *  Will create a Variable, given a command to set the variable with.
 */
class CreateVariableCommand : public Command {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ---------
    CreateVariableCommand(smart_ptr<Command> cmd) : m_Cmd(cmd) {};
    ~CreateVariableCommand() = default;

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    void execute() {
        // create a new smartPtr for a new Variable with the given command
        smart_ptr<Variable<Command>> smartPtr(new Variable<Command>(m_Cmd));
        this->m_Var = smartPtr;
    };

private:
    smart_ptr<Command> m_Cmd;
    smart_ptr<Variable<Command>> m_Var = nullptr;
};


#endif //AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
