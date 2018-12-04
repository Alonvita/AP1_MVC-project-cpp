cmake_minimum_required(VERSION 3.12)
project(AP1_Semetser_Project)

set(CMAKE_CXX_STANDARD 14)

set(MAIN main.cpp)

set(UTILITIES
        #Reference Count
        Utilities/Reference_Counting/ReferenceCount.h
        #Smart Pointers
        Utilities/Reference_Counting/SmartPtr.h)

set(FILE_PARSING
        # Lexer
        File_Parsing/Consile_File_Reading/Lexer.cpp File_Parsing/Consile_File_Reading/Lexer.h
        # Strings Validator
        File_Parsing/Parsing/StringValidator.cpp File_Parsing/Parsing/StringValidator.h
        # Variables
        File_Parsing/Variables/Variable.cpp File_Parsing/Variables/Variable.h)

set(COMMANDS
        # Test Printing Command
        Commands/TestPrintCommand.h
        # Interface
        Commands/Command.h

        )

add_executable(projectExecutable ${MAIN} ${FILE_PARSING} ${COMMANDS} ${UTILITIES})