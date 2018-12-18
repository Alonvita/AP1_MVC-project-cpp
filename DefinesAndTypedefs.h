//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H
#define AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H

#include <map>
#include <list>
#include <queue>

#define BIND_COMMAND_STR "bind_command"
#define OPERATOR_COMMAND_STR "operator"
#define SLEEP_COMMAND_STR "sleep_command"
#define WHILE_LOOP_COMMAND_STR "while_loop"
#define CREATE_VAR_COMMAND_STR "make_var_command"
#define ASSIGN_EXISTING_COMMAND_STR "assign_existing"
#define CALCULATE_MATH_COMMAND_STR "calculate_math_expression"

typedef const std::string& ConstStringRef;
typedef std::list<std::string> StringsList;
typedef std::pair<std::string, std::string> StringsPair;

typedef std::queue<StringsPair> StringsPairQueue;

#endif //AP1_SEMETSER_PROJECT_DEFINESANDTYPEDEFS_H
