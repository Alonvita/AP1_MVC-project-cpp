cmake_minimum_required(VERSION 3.12)
project(AP1_Semetser_Project)

set(CMAKE_CXX_STANDARD 14)

set(MAIN main.cpp)

set(UTILITIES
        # Reference Count
        Utilities/Reference_Counting/ReferenceCount.h
        # Smart Pointers
        Utilities/Reference_Counting/SmartPtr.h
        )

set(SHARED_DATA
        #Message
        Shared_Data/Message.h
        #Command Result
        Shared_Data/CommandResult.h
        #Notification
        Shared_Data/Notification.h
        )

set(OUTER_HANDLERS
        #VariableMapContainer
        Controller/VariablesMapContainer.cpp Controller/VariablesMapContainer.h
        #MathExpressionsHandler
        Controller/Math_Expressions_Handling/MathExpressionsHandler.cpp Controller/Math_Expressions_Handling/MathExpressionsHandler.h
        #OperatorsHandler
        Controller/Operators_Handler/OperatorsHandler.cpp Controller/Operators_Handler/OperatorsHandler.h
        )

set(MATH_EXP_PARSING_UTIL
        #Utility
        Controller/Utility/UtilityFunctions.cpp Controller/Utility/UtilityFunctions.h)

set(CONTROLLER
        #Controller
        Controller/Controller.cpp Controller/Controller.h
        # Test Printing ICommand -- will be used for testing stuff
        Controller/Commands/TestPrintCommand.h
        # Interface
        Controller/Commands/ICommand.h
        # CreateVariableCommand
        Controller/Commands/CreateVariableCommand.cpp Controller/Commands/CreateVariableCommand.h
        # BindCommand
        Controller/Commands/BindCommand.cpp Controller/Commands/BindCommand.h
        #OperatorCommand
        Controller/Commands/OperatorCommand.cpp Controller/Commands/OperatorCommand.h
        )

set(CLIENTS
        #Interface
        View/IClient.h
        #Client
        View/Client.cpp View/Client.h
        )

add_executable(projectExecutable ${MAIN} ${SHARED_DATA} ${CONTROLLER} ${UTILITIES} ${CLIENTS} ${OUTER_HANDLERS} ${MATH_EXP_PARSING_UTIL})