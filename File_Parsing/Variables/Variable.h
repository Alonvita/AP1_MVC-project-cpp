//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARIABLE_H
#define AP1_SEMETSER_PROJECT_VARIABLE_H

#include "../../Commands/Command.h"
#include "../../Utilities/Reference_Counting/SmartPtr.h"

using namespace std;

/**
 * Variable.
 *  A variable will hold a unique command pointerCommand in it.
 *
 */
class Variable {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    Variable(smart_ptr<Command>& cmd) : cmd(cmd) {};

    /// ---------- GETTERS & SETTERS ----------
    // Executes the command
    void execute_command() { this->cmd->execute(); }

private:
    smart_ptr<Command> cmd;
};


#endif //AP1_SEMETSER_PROJECT_VARIABLE_H
