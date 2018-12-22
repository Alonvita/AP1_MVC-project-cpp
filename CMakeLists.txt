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
        Shared_Data/Lexer.cpp Shared_Data/Lexer.h
        # Command Data
        Shared_Data/CommandData.h Shared_Data/CommandData.cpp
        )

set(OUTER_HANDLERS
        #VariableMapContainer
        Controller/VariablesMapContainer.cpp Controller/VariablesMapContainer.h
        #MathExpressionsHandler
        Controller/Math_Expressions_Handling/MathExpressionsHandler.cpp Controller/Math_Expressions_Handling/MathExpressionsHandler.h
        #OperatorsHandler
        Controller/Operators_Handler/OperatorsHandler.cpp Controller/Operators_Handler/OperatorsHandler.h
        )

set(CONTROLLER
        #Controller
        Controller/Controller.cpp Controller/Controller.h
        # Test Printing ICommand -- will be used for testing stuff
        # Interface
        Controller/Commands/ICommand.h
        # CreateVariableCommand
        Controller/Commands/CreateVariableCommand.cpp Controller/Commands/CreateVariableCommand.h
        # BindCommand
        Controller/Commands/BindCommand.cpp Controller/Commands/BindCommand.h
        #OperatorCommand
        Controller/Commands/OperatorCommand.cpp Controller/Commands/OperatorCommand.h
        #CalculateMathExpressionCommand
        Controller/Commands/CalculateMathExpressionCommand.cpp Controller/Commands/CalculateMathExpressionCommand.h
        # While Loop Command
        Controller/Commands/WhileLoopCommand.cpp Controller/Commands/WhileLoopCommand.h
        # Assign Existing Var
        Controller/Commands/AssignExistingVarCommand.cpp Controller/Commands/AssignExistingVarCommand.h
        # Sleep Command
        Controller/Commands/SleepCommand.cpp Controller/Commands/SleepCommand.h
        )

set(CLIENTS
        #Interface
        View/IClient.h
        #Client
        View/Client.cpp View/Client.h
        )

add_executable(projectExecutable ${UTILITIES} ${MAIN} ${SHARED_DATA} ${CONTROLLER} ${CLIENTS} ${OUTER_HANDLERS})