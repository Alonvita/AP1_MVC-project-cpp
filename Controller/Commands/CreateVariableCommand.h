//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
#define AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H


#include <map>

#include <typeinfo>
#include <sstream>

#include "ICommand.h"
#include "../../Utilities/Reference_Counting/SmartPtr.h"
#include "../Math_Expressions_Handling/MathExpressionsHandler.h"

/**
 * CreateVariableCommand.
 *  Will create a Variable, given a command to set the variable with.
 */
class CreateVariableCommand : public ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ---------
    ~CreateVariableCommand() = default;
    explicit CreateVariableCommand(VariablesMapContainer* variablesMapContainer) : m_vContainer(variablesMapContainer) {};

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    CommandResult execute(IClient* sender, ConstStringRef command, VarData* placeHolder) override;

private:
    VariablesMapContainer* m_vContainer;
};


#endif //AP1_SEMETSER_PROJECT_CREATEVARIABLECOMMAND_H
