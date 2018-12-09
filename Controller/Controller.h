//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>
#include <queue>

#include "Commands/ICommand.h"
#include "Commands/BindCommand.h"
#include "../Shared_Data/CommandResult.h"
#include "Commands/CreateVariableCommand.h"
#include "Math_Expressions_Handling/MathExpressionsHandler.h"

#define MAKE_VAR_COMMAND_STR "make_var_command"
#define BIND_COMMAND_STR "bind_command"

class Controller {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller();

    /// -------- EXECUTION --------
    CommandResult executeCommand(std::queue<std::pair<std::string, std::string>>& commandsQueue, IClient* sender);


private:
    vector<var_data*> m_placeHolder;
    VariablesMapContainer* m_vContainer;
    unsigned long m_placeHolderCount = 1;
    std::map<std::string, ICommand*> m_commandsList;
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
