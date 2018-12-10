//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>
#include <queue>

#include "Commands/ICommand.h"
#include "Commands/BindCommand.h"
#include "../DefinesAndTypedefs.h"
#include "../Shared_Data/CommandResult.h"
#include "Commands/CreateVariableCommand.h"
#include "Math_Expressions_Handling/MathExpressionsHandler.h"
#include "Operators_Handler/OperatorsHandler.h"

#define OPERATOR_COMMAND_STR "operator"
#define BIND_COMMAND_STR "bind_command"
#define CREATE_VAR_COMMAND_STR "make_var_command"
#define WHILE_LOOP_COMMAND_STR "while_loop"
#define CALCULATE_MATH_COMMAND_STR "calcuate_math_expression"

class Controller {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller();

    /// -------- EXECUTION --------
    CommandResult executeCommand(std::queue<std::pair<std::string, std::string>>& commandsQueue, IClient* sender);


private:
    CommandsMap m_commandsList;
    OperatorsHandler* m_opHandler;
    vector<var_data*> m_placeHoldersContainer;
    VariablesMapContainer* m_vContainer;
    unsigned long m_placeHolderCount = 1;
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
