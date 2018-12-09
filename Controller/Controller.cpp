//
// Created by alon on 07/12/18.
//

#include "Controller.h"

///---------- CONSTRUCTORS & DESTRUCTORS ----------

/**
 * Controller().
 */
Controller::Controller() {
    this->m_vContainer = new VariablesMapContainer();

    // initialize Math Parser
    this->m_mathExpressionsHandler = new MathExpressionsHandler(m_vContainer);

    // Initialize Commands Map
    this->m_commandsList.insert(make_pair(BIND_COMMAND_STR, new BindCommand())); // Create Var
    this->m_commandsList.insert(make_pair(MAKE_VAR_COMMAND_STR, new CreateVariableCommand(m_vContainer))); // Create Var
}

/**
 * ~Controller().
 */
Controller::~Controller() {
    // delete the math handler
    delete this->m_mathExpressionsHandler;
    delete this->m_vContainer;

    // delete every command on the command list
    for(std::pair<std::string, ICommand*> p : this->m_commandsList)
        delete p.second;

    for(var_data* vd : this->m_placeHolder)
        free(vd);
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
CommandResult Controller::executeCommand(std::queue<std::pair<std::string, std::string>>& commandsQueue, IClient* sender) {
    // TODO: TEST CODE -> remove
    /*
    auto temp = (var_data*) malloc(sizeof(var_data));
    int fp = open("/home/alon/Desktop/Untitled Folder/test.txt" ,O_RDWR);
    double d = 1234.124;
    write(fp, &d, sizeof(double));
    lseek(fp, 0, SEEK_SET);

    temp->set_data(&fp);
    temp->set_type(BIND_COMMAND);
    m_placeHolder.push_back(temp);
     */

    var_data* temp = nullptr;

    // Undefined command
    CommandResult commandResult(false, EMPTY_QUEUE, "commandsQueue passed empty.\n", true);

    while(!commandsQueue.empty()) {
        // take front
        pair<std::string,std::string> command = commandsQueue.front();

        // find commandsQueue in map
        auto it = m_commandsList.find(command.first);

        // if not contains
        if (it == m_commandsList.end())
            return CommandResult(false, UNDEFINED, "Unknown Command\n", true); // return unknown commandsQueue

        commandResult = (*it).second->execute(nullptr, command.second, temp);

        m_placeHolderCount++;
        commandsQueue.pop(); // pop the used command
    }

    return commandResult;
}