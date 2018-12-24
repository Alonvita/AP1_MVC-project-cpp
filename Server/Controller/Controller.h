//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>

#include "Commands/ControllerCommands/IfCommand.h"
#include "Commands/ControllerCommands/BindCommand.h"
#include "Commands/ControllerCommands/SleepCommand.h"
#include "../../DefinesAndTypedefs.h"
#include "Commands/ControllerCommands/OperatorCommand.h"
#include "Commands/ControllerCommands/WhileLoopCommand.h"
#include "Commands/ControllerCommands/IControllerCommand.h"
#include "Commands/ControllerCommands/CreateVariableCommand.h"
#include "../../Shared_Data/CommandResult.h"
#include "Commands/ControllerCommands/AssignExistingVarCommand.h"
#include "Operators_Handler/OperatorsHandler.h"
#include "Commands/ControllerCommands/CalculateMathExpressionCommand.h"
#include "Math_Expressions_Handling/MathExpressionsHandler.h"

#define CHECK_SERVER_RUNNING !m_serverRunning && command->getName() != CONNECT_TO_SERVER_COMMAND_STR

class Controller : public IController {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller() override;

    /// -------- EXECUTION --------
    CommandResult executeCommand(const CommandDataQueue& commandsQueue, IClient* sender) override;

private:
    bool m_serverRunning;
    ControllerCommandsMap m_commandsList;
    OperatorsHandler* m_opHandler;
    VariablesMapContainer* m_vContainer;
    unsigned long m_placeHolderCount = 0;
    std::vector<VarData*> m_placeHoldersContainer;
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
