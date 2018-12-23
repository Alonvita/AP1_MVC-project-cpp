//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H
#define AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H

#include <map>
#include <list>
#include <queue>
#include <vector>
#include "Utility/GenericFunctions.cpp"

/// ---- OPERATORS ----
#define LT "<"
#define GT ">"
#define LE "<="
#define GE ">="
#define EQ "=="

#define OPERATORS_LIST { LT, GT, LE, GE, EQ }
#define MATH_OPERATIONS { "*", "/", "+", "-", "%" }

/// ---- LEXER ----
#define RAW_ASSIGN_STR "="
#define RAW_BIND_STR "bind"
#define RAW_SLEEP_STR "sleep"
#define RAW_PRINT_STR "print"
#define RAW_OPEN_BRACKETS "{"
#define RAW_CLOSE_BRACKETS "}"
#define RAW_IF_COMMAND_STR "if"
#define RAW_WHILE_LOOP_STR "while"
#define RAW_CLOSE_COMMAND_STR "close"
#define RAW_CREATE_VARIABLE_STR "var"
#define RAW_CONNECT_TO_SEVER_STR "connect"
#define RAW_OPEN_SERVER_STR "openDataServer"

/// ---- COMMANDS ----
#define IF_COMMAND_STR "IF"
#define BIND_COMMAND_STR "BIND"
#define CLOSE_COMMAND_STR "CLOSE"
#define SLEEP_COMMAND_STR "SLEEP"
#define PRINT_COMMAND_STR "PRINT"
#define OPERATOR_COMMAND_STR "OPERATOR"
#define CREATE_VAR_COMMAND_STR "MAKE_VAR"
#define WHILE_LOOP_COMMAND_STR "WHILE_LOOP"
#define ASSIGN_EXISTING_COMMAND_STR "ASSIGN"
#define CALCULATE_MATH_COMMAND_STR "CALCULATE_MATH_EXPRESSION"

#define SAFELY_POP_COMMAND_DATA_QUEUE(queue) delete(queue.front()); queue.pop();

typedef std::initializer_list<std::string> StringsInitializeList;
typedef std::pair<char*, double> VarDataPair;

typedef const std::string& ConstStringRef;
typedef std::list<std::string> StringsList;
typedef std::vector<std::string> StringsVector;
typedef std::pair<std::string, std::string> StringsPair;

typedef std::queue<StringsPair> StringsPairsQueue;
typedef std::vector<StringsPair> StringsPairsVector;

#endif //AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H
