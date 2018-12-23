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
    m_mathExpressionsHandler = new MathExpressionsHandler(m_vContainer);

    // initialize opHandler
    m_opHandler = new OperatorsHandler(m_mathExpressionsHandler);

    // initialize PH container
    m_placeHoldersContainer.push_back(new VarData());

    // Initialize Commands Map
    m_commandsList.insert(std::make_pair(SLEEP_COMMAND_STR, new SleepCommand()));
    m_commandsList.insert(std::make_pair(BIND_COMMAND_STR, new BindCommand())); // Create Var
    m_commandsList.insert(std::make_pair(IF_COMMAND_STR, new IfCommand(this, &m_commandsList)));
    m_commandsList.insert(std::make_pair(OPERATOR_COMMAND_STR, new OperatorCommand(m_opHandler)));
    m_commandsList.insert(std::make_pair(WHILE_LOOP_COMMAND_STR, new WhileLoopCommand(this, &m_commandsList)));
    m_commandsList.insert(std::make_pair(CREATE_VAR_COMMAND_STR, new CreateVariableCommand(m_vContainer))); // Create Var
    m_commandsList.insert(std::make_pair(CALCULATE_MATH_COMMAND_STR, new CalculateMathExpressionCommand(m_mathExpressionsHandler)));
    m_commandsList.insert(std::make_pair(ASSIGN_EXISTING_COMMAND_STR, new AssignExistingVarCommand(m_vContainer ,m_mathExpressionsHandler)));
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

    for(VarData* vd : this->m_placeHoldersContainer)
        delete(vd);
}

///---------- EXECUTION ----------

/**
 * executeCommand(std::queue<std::string>& commandsQueue, int client).
 *
 * @param commandsQueue StringsPairQueue& -- a queue of pairs of strings:
 *                                              pair.first <- command as string
 *                                              pair.second <- params
 * @param socketID int -- sender client's socket.
 *
 * @return a command result created by the command's execution.
 */
CommandResult Controller::executeCommand(const CommandDataQueue& commandsQueue, IClient* sender) {
    // Undefined command
    CommandResult commandResult;
    CommandDataQueue queueCpy = commandsQueue;

    while(!queueCpy.empty()) {
        m_placeHoldersContainer.push_back(new VarData());
        m_placeHolderCount++;

        // take front
        CommandData* command = queueCpy.front();

        // find commandsQueue in map
        auto it = m_commandsList.find(command->getName());

        // if not contains
        if (it == m_commandsList.end()) {
            return CommandResult(false, UNDEFINED, "Unknown Command\n", true); // return unknown commandsQueue
        }

        VarData* currPH = m_placeHoldersContainer[m_placeHolderCount];
        VarData* lastPH = m_placeHoldersContainer[m_placeHolderCount - 1];

        // TODO: I think mutex lock will be here
        commandResult = (*it).second->execute(nullptr, command, lastPH, currPH);

        if(!commandResult.commandSucceeded())
            return CommandResult(false, EXECUTION_FAILURE, commandResult.getData(), true);

        queueCpy.pop();

        if(commandsQueue.empty()) {
            break;
        }
    }

    return commandResult;
}