//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
#define AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H


#include "ICommand.h"
#include "Variables/Variable.h"
#include "../../Utilities/Reference_Counting/SmartPtr.h"

/**
 * CreateVariableCommand.
 *  Will create a Variable, given a command to set the variable with.
 */
class CreateVariableCommand : public ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ---------
    CreateVariableCommand(smart_ptr<ICommand> cmd) : m_Cmd(cmd) {};
    ~CreateVariableCommand() = default;

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    CommandResult execute(IClient* sender, const std::string& command) {
        // create a new smartPtr for a new Variable with the given m_command
        this->m_Var = smart_ptr<Variable<ICommand>>(new Variable<ICommand>(m_Cmd));
    };

private:
    smart_ptr<ICommand> m_Cmd;
    smart_ptr<Variable<ICommand>> m_Var;
};


#endif //AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
