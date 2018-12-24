cmake_minimum_required(VERSION 3.12)
project(AP1_Semetser_Project)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread -Wextra")

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
        Server/Controller/VariablesMapContainer.h Server/Controller/VariablesMapContainer.cpp
        #MathExpressionsHandler
        Server/Controller/Math_Expressions_Handling/MathExpressionsHandler.h Server/Controller/Math_Expressions_Handling/MathExpressionsHandler.cpp
        #OperatorsHandler
        Server/Controller/Operators_Handler/OperatorsHandler.h Server/Controller/Operators_Handler/OperatorsHandler.cpp
        )

set(SERVER
        ### THREADING ###
        Server/ThreadPool/Task.h
        Server/ThreadPool/Thread.h Server/ThreadPool/Thread.cpp
        Server/ThreadPool/WorkQueue.h Server/ThreadPool/WorkQueue.cpp
        Server/ThreadPool/ThreadPool.h Server/ThreadPool/ThreadPool.cpp
        Server/ThreadPool/PoolWorkerThread.h Server/ThreadPool/PoolWorkerThread.cpp

        #IServer
        Server/IServer.h
        # TCPServer
        Server/TCPServer.h Server/TCPServer.cpp
        # FlightGearClientHandler
        Server/ClientHandler/FlightGearClientHandler.h Server/ClientHandler/FlightGearClientHandler.cpp

        #IClientHandler
        Server/ClientHandler/IClientHandler.h
        #ClientHandler
        Server/ClientHandler/ClientHandler.h Server/ClientHandler/ClientHandler.cpp
        #IController
        Server/Controller/IController.h
        #Controller
        Server/Controller/Controller.h Server/Controller/Controller.cpp
        # Test Printing ICommand -- will be used for testing stuff
        # Interface
        Server/Controller/Commands/ICommand.h
        # CreateVariableCommand
        Server/Controller/Commands/CreateVariableCommand.h Server/Controller/Commands/CreateVariableCommand.cpp
        # BindCommand
        Server/Controller/Commands/BindCommand.h Server/Controller/Commands/BindCommand.cpp
        #OperatorCommand
        Server/Controller/Commands/OperatorCommand.h Server/Controller/Commands/OperatorCommand.cpp
        #CalculateMathExpressionCommand
        Server/Controller/Commands/CalculateMathExpressionCommand.h Server/Controller/Commands/CalculateMathExpressionCommand.cpp
        # While Loop Command
        Server/Controller/Commands/WhileLoopCommand.h Server/Controller/Commands/WhileLoopCommand.cpp
        # Assign Existing Var
        Server/Controller/Commands/AssignExistingVarCommand.h Server/Controller/Commands/AssignExistingVarCommand.cpp
        # Sleep Command
        Server/Controller/Commands/SleepCommand.h Server/Controller/Commands/SleepCommand.cpp
        # If Command
        Server/Controller/Commands/IfCommand.h Server/Controller/Commands/IfCommand.cpp
        # Start Server Command
        Server/Controller/Commands/StartServerCommand.h Server/Controller/Commands/StartServerCommand.cpp
        )

set(CLIENTS
        #Interface
        View/IClient.h
        #Client
        View/Client.cpp View/Client.h
        )

add_executable(projectExecutable ${UTILITIES} ${MAIN} ${SHARED_DATA} ${SERVER} ${CLIENTS} ${OUTER_HANDLERS})