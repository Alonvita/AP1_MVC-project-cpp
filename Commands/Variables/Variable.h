//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARIABLE_H
#define AP1_SEMETSER_PROJECT_VARIABLE_H

#include "../Command.h"
#include "../../Utilities/Reference_Counting/SmartPtr.h"

using namespace std;

/**
 * Variable.
 *  A variable will hold a smart_ptr to a typename T.
 *
 * @tparam T template <typename T> -- an object of type T.
 */
template <typename T>
class Variable {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    Variable(smart_ptr<T>& cmd) : cmd(cmd) {};

    /// ---------- GETTERS & SETTERS ----------
    // Executes the command
    smart_ptr<T> get_object() { return this->cmd; }

private:
    smart_ptr<T> cmd;
};


#endif //AP1_SEMETSER_PROJECT_VARIABLE_H
