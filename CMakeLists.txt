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

        ### SERVER CREATION & CONNECTION HANDLING ###
        # Start Server Command
        Server/ServerOpenAndConnection/StartServerCommand.h Server/ServerOpenAndConnection/StartServerCommand.cpp
        # Connect to Server Command
        Server/ServerOpenAndConnection/ConnectToServerCommand.h Server/ServerOpenAndConnection/ConnectToServerCommand.cpp
        # Tasks
        Server/ServerOpenAndConnection/ConnectToServer.h Server/ServerOpenAndConnection/ConnectToServer.cpp
        Server/ServerOpenAndConnection/OpenServer.h Server/ServerOpenAndConnection/OpenServer.cpp

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

        ### COMMANDS ###
        # ICommand
        Server/ICommand.h
        # IServerHandlingCommand
        Server/ServerOpenAndConnection/IServerHandlingCommand.h
        # IControllerCommand
        Server/Controller/Commands/ControllerCommands/IControllerCommand.h
        # CreateVariableCommand
        Server/Controller/Commands/ControllerCommands/CreateVariableCommand.h Server/Controller/Commands/ControllerCommands/CreateVariableCommand.cpp
        # BindCommand
        Server/Controller/Commands/ControllerCommands/BindCommand.h Server/Controller/Commands/ControllerCommands/BindCommand.cpp
        #OperatorCommand
        Server/Controller/Commands/ControllerCommands/OperatorCommand.h Server/Controller/Commands/ControllerCommands/OperatorCommand.cpp
        #CalculateMathExpressionCommand
        Server/Controller/Commands/ControllerCommands/CalculateMathExpressionCommand.h Server/Controller/Commands/ControllerCommands/CalculateMathExpressionCommand.cpp
        # While Loop Command
        Server/Controller/Commands/ControllerCommands/WhileLoopCommand.h Server/Controller/Commands/ControllerCommands/WhileLoopCommand.cpp
        # Assign Existing Var
        Server/Controller/Commands/ControllerCommands/AssignExistingVarCommand.h Server/Controller/Commands/ControllerCommands/AssignExistingVarCommand.cpp
        # Sleep Command
        Server/Controller/Commands/ControllerCommands/SleepCommand.h Server/Controller/Commands/ControllerCommands/SleepCommand.cpp
        # If Command
        Server/Controller/Commands/ControllerCommands/IfCommand.h Server/Controller/Commands/ControllerCommands/IfCommand.cpp
        )

set(CLIENTS
        #Interface
        View/IClient.h
        #Client
        View/Client.cpp View/Client.h
        )

add_executable(projectExecutable ${UTILITIES} ${MAIN} ${SHARED_DATA} ${SERVER} ${CLIENTS} ${OUTER_HANDLERS})