//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARIABLE_H
#define AP1_SEMETSER_PROJECT_VARIABLE_H

#include "../ICommand.h"
#include "../../../Utilities/Reference_Counting/SmartPtr.h"

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
    Variable(smart_ptr<T>& obj) : m_Obj(obj) {};

    /// ---------- GETTERS & SETTERS ----------
    // Executes the m_command
    smart_ptr<T> get_object() { return this->m_Obj; }

    /// ---------- OPERATORS OVERRIDING ----------
    Variable<T>& operator=(const smart_ptr<T>& other) {
        this->m_Obj = other;

        return *this;
    }

    Variable<T>& operator=(const T& other) {
        smart_ptr<T> other_prt = other;
        this->m_Obj = other_prt;
    }

private:
    smart_ptr<T> m_Obj;
};


#endif //AP1_SEMETSER_PROJECT_VARIABLE_H
