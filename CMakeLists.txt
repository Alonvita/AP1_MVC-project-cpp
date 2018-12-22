cmake_minimum_required(VERSION 3.12)
project(AP1_Semetser_Project)

set(CMAKE_CXX_STANDARD 14)

set(MAIN main.cpp)

set(UTILITIES
        # Defines and Typedefs
        DefinesAndTypedefs.h
        # Variable Data Class
        Utility/VarData.h Utility/VarData.cpp
        # Utility Functions
        Utility/UtilityFunctions.h Utility/UtilityFunctions.cpp
        # Generic Functions
        Utility/GenericFunctions.h Utility/GenericFunctions.cpp
        # MyPriorityQueue
        )

set(SHARED_DATA
        # Message
        Shared_Data/Message.h
        # Command Result
        Shared_Data/CommandResult.h
        # Notification
        Shared_Data/Notification.h
        # Lexer
        Shared_Data/Lexer.h Shared_Data/Lexer.cpp
        # Command Data
        Shared_Data/CommandData.cpp Shared_Data/CommandData.h
        )

set(OUTER_HANDLERS
        #VariableMapContainer
        Controller/VariablesMapContainer.h Controller/VariablesMapContainer.cpp
        #MathExpressionsHandler
        Controller/Math_Expressions_Handling/MathExpressionsHandler.h Controller/Math_Expressions_Handling/MathExpressionsHandler.cpp
        #OperatorsHandler
        Controller/Operators_Handler/OperatorsHandler.h Controller/Operators_Handler/OperatorsHandler.cpp
        )

set(CONTROLLER
        #Controller
        Controller/Controller.h Controller/Controller.cpp
        # Test Printing ICommand -- will be used for testing stuff
        # Interface
        Controller/Commands/ICommand.h
        # CreateVariableCommand
        Controller/Commands/CreateVariableCommand.h Controller/Commands/CreateVariableCommand.cpp
        # BindCommand
        Controller/Commands/BindCommand.h Controller/Commands/BindCommand.cpp
        #OperatorCommand
        Controller/Commands/OperatorCommand.h Controller/Commands/OperatorCommand.cpp
        #CalculateMathExpressionCommand
        Controller/Commands/CalculateMathExpressionCommand.h Controller/Commands/CalculateMathExpressionCommand.cpp
        # While Loop Command
        Controller/Commands/WhileLoopCommand.h Controller/Commands/WhileLoopCommand.cpp
        # Assign Existing Var
        Controller/Commands/AssignExistingVarCommand.h Controller/Commands/AssignExistingVarCommand.cpp
        # Sleep Command
        Controller/Commands/SleepCommand.h Controller/Commands/SleepCommand.cpp
        # If Command
        Controller/Commands/IfCommand.h Controller/Commands/IfCommand.cpp
        # Commands Util
        Controller/Commands/CommandsUtil/CommandsUtil.h Controller/Commands/CommandsUtil/CommandsUtil.cpp
        )

set(CLIENTS
        #Interface
        View/IClient.h
        #Client
        View/Client.cpp View/Client.h
        )

add_executable(projectExecutable ${UTILITIES} ${MAIN} ${SHARED_DATA} ${CONTROLLER} ${CLIENTS} ${OUTER_HANDLERS})