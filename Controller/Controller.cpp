//
// Created by alon on 07/12/18.
//

#include "Controller.h"

///---------- CONSTRUCTORS & DESTRUCTORS ----------

/**
 * Controller().
 */
Controller::Controller() {
    // initialzie placeholder count
    m_placeHolderCount = 1;

    // initialize Math Parser
    this->m_mathExpressionsParser = new MathExpressionsParser();

    // Initialize Commands Map
    this->m_commandsList.insert(make_pair(MAKE_VAR_STR, new CreateVariableCommand(m_mathExpressionsParser))); // Create Var
}

/**
 * ~Controller().
 */
Controller::~Controller() {
    // delete the math expressions parser
    delete this->m_mathExpressionsParser;

    // delete every command on the command list
    for(std::pair<std::string, ICommand*> p : this->m_commandsList) {
        delete p.second;
    }
}

///---------- EXECUTION ----------

/**
 * executeCommand(std::queue<std::string>& commandsQueue, int client).
 *
 * @param commandsQueue std::queue<std::string>& -- a queue of strings representing commands.
 * @param socketID int -- sender client's socket.
 *
 * @return a command result created by the command's execution.
 */
CommandResult Controller::executeCommand(std::queue<std::string>& commandsQueue, IClient* sender) {

    // HARD TRIAL
    double d = 17;
    this->m_placeHolder.push_back(&d);

    CommandResult commandResult(false, UNDEFINED, "Unknown Command\n", true);

    while(!commandsQueue.empty()) {
        // take front
        std::string command = commandsQueue.front();
        commandsQueue.pop(); // and pop it

        // find commandsQueue in map
        auto it = m_commandsList.find(command);

        // if not contains
        if (it == m_commandsList.end())
            return CommandResult(false, UNDEFINED, "Unknown Command\n", true); // return unknown commandsQueue

        commandResult = (*it).second->execute(nullptr, "nada", m_placeHolder[m_placeHolderCount - 1]);
        if(commandsQueue.empty()) {
            break;
        }
    }

    return commandResult;
}