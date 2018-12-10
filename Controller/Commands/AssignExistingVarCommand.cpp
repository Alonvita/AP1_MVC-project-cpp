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
    // Local Variables
    auto val = (double*) malloc(sizeof(double));

    try {
        StringsList sList;
        splitStringToList(command, " ", sList, false);

        auto it = sList.begin(); // iterator
        std::string varName = (*it++); // take variable name
        std::string expression = (*it); // take value
        *val = m_mathExpressionsHandler->parse_mathematical_expression(expression);

        this->m_vMapContainer->setExistingVar(varName, val, DOUBLE);

        std::stringstream ss;
        ss << "Variable: \"" << varName << "\" was assigned successfully from expression: \"" << \
            expression << "\", yielding the value: " << (*val);


        return CommandResult(true, ASSIGN_VAR, ss.str(), true);
    } catch(std::exception& e) {
        free(val);
        return CommandResult(false, EXECUTION_FAILURE, e.what(), true);
    }
}