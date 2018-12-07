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
    void execute() {
        // create a new smartPtr for a new Variable with the given m_command
        smart_ptr<Variable<ICommand>> smartPtr(new Variable<ICommand>(m_Cmd));
        this->m_Var = smartPtr;
    };

private:
    smart_ptr<ICommand> m_Cmd;
    smart_ptr<Variable<ICommand>> m_Var = nullptr;
};


#endif //AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
