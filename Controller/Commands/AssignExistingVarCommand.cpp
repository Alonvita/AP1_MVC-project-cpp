//
// Created by alon on 10/12/18.
//

#include "AssignExistingVarCommand.h"

/**
 * execute(IClient* sender, const std::string& command, void* placeHolder).
 *
 * @param sender IClient* -- a pointer to the sending cliend.
 * @param command const std::string& -- a constant reference to a string representing the command.
 *                      Convention:
 *                          [variable name] [expression]
 *
 * @param placeHolder var_data* -- a placeholder.
 *
 * @return a command result, depending on the specific executed command and it's success/failure.
 */
CommandResult AssignExistingVarCommand::execute(IClient* sender, ConstStringRef command, VarData* placeHolder) {
    try {
        StringsList sList;
        splitStringToList(command, " ", sList, false);

        auto it = sList.begin(); // iterator
        std::string varName = (*it++); // take variable name
        std::string expression = (*it); // take value

        auto val = (double*) malloc(sizeof(double));
        *val = m_mathExpressionsHandler->parse_mathematical_expression(expression);

        this->m_vMapContainer->setExistingVar(varName, val, BOOL);

        std::stringstream ss;
        ss << "Var: " << varName << " was assigned successfully from expression: " << \
            expression << ",\n\t yielding the value: " << (*val);


        return CommandResult(true, ASSIGN_VAR, ss.str(), true);
    } catch(std::exception& e) {
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}