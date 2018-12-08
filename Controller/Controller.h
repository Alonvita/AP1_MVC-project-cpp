//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>
#include <queue>

#include "Commands/ICommand.h"
#include "../Shared_Data/CommandResult.h"
#include "Commands/CreateVariableCommand.h"
#include "Math_Expressions_Parsing/MathExpressionsParser.h"

#define MAKE_VAR_STR "make_var"

class Controller {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller();

    /// -------- EXECUTION --------

    // TODO: after creating the client, this function should receive IClient* client and not an integer
    CommandResult executeCommand(std::queue<std::string>& commandsQueue, IClient* sender);


private:
    unsigned long m_placeHolderCount;
    vector<void*> m_placeHolder;
    MathExpressionsParser* m_mathExpressionsParser;
    std::map<std::string, ICommand*> m_commandsList;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
