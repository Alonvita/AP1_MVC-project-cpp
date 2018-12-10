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

    // TODO: TEMP USEAGE -> REMOVE THIS
    auto a = new var_data;
    auto d = (double*) malloc(sizeof(double));
    *d = 15;

    a->set_type(DOUBLE);
    a->set_data(&(*d));
    d = nullptr;

    m_vContainer->addToMap("a", a);


    // TODO: UNTIL HERE

    // initialize opHandler
    this->m_opHandler = new OperatorsHandler(m_vContainer);

    // initialize Math Parser
    this->m_mathExpressionsHandler = new MathExpressionsHandler(m_vContainer);

    // Initialize Commands Map
    this->m_commandsList.insert(make_pair(BIND_COMMAND_STR, new BindCommand())); // Create Var
    this->m_commandsList.insert(make_pair(OPERATOR_COMMAND_STR, new OperatorCommand(m_opHandler)));
    this->m_commandsList.insert(make_pair(WHILE_LOOP_COMMAND_STR, new WhileLoopCommand(&m_commandsList)));
    this->m_commandsList.insert(make_pair(CREATE_VAR_COMMAND_STR, new CreateVariableCommand(m_vContainer))); // Create Var
    this->m_commandsList.insert(make_pair(CALCULATE_MATH_COMMAND_STR, new CalculateMathExpressionCommand(m_mathExpressionsHandler)));
}

/**
 * ~Controller().
 */
Controller::~Controller() {
    // delete the math handler
    delete this->m_mathExpressionsHandler;
    delete this->m_opHandler;
    delete this->m_vContainer;

    // delete every command on the command list
    for(CommandsMapPair p : this->m_commandsList)
        delete p.second;

    for(var_data* vd : this->m_placeHoldersContainer) {
        free(vd);
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
CommandResult Controller::executeCommand(std::queue<StringsPair>& commandsQueue, IClient* sender) {
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

    // add temp to our placeHolder vector
    m_placeHoldersContainer.push_back((var_data*) malloc(sizeof(var_data)));

    // Undefined command
    CommandResult commandResult(false, EMPTY_QUEUE, "commandsQueue passed empty.\n", true);

    while(true) {
        // take front
        StringsPair command = commandsQueue.front();

        // find commandsQueue in map
        auto it = m_commandsList.find(command.first);

        // if not contains
        if (it == m_commandsList.end())
            return CommandResult(false, UNDEFINED, "Unknown Command\n", true); // return unknown commandsQueue

        commandResult = (*it).second->execute(nullptr, command.second, m_placeHoldersContainer[m_placeHolderCount - 1]);

        m_placeHolderCount++;
        commandsQueue.pop(); // pop the used command
        if(commandsQueue.empty())
            break;
    }

    return commandResult;
}