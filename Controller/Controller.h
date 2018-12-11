//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>

#include "Commands/ICommand.h"
#include "Commands/BindCommand.h"
#include "../DefinesAndTypedefs.h"
#include "Commands/SleepCommand.h"
#include "Commands/OperatorCommand.h"
#include "Commands/WhileLoopCommand.h"
#include "../Shared_Data/CommandResult.h"
#include "Commands/CreateVariableCommand.h"
#include "Commands/AssignExistingVarCommand.h"
#include "Operators_Handler/OperatorsHandler.h"
#include "Commands/CalculateMathExpressionCommand.h"
#include "Math_Expressions_Handling/MathExpressionsHandler.h"


class Controller {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller();

    /// -------- EXECUTION --------
    CommandResult executeCommand(StringsPairQueue& commandsQueue, IClient* sender);


private:
    CommandsMap m_commandsList;
    OperatorsHandler* m_opHandler;
    VariablesMapContainer* m_vContainer;
    unsigned long m_placeHolderCount = 0;
    std::vector<VarData*> m_placeHoldersContainer;
    MathExpressionsHandler* m_mathExpressionsHandler;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
