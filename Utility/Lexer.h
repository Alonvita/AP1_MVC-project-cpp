//
// Created by alon on 11/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_LEXER_H
#define AP1_SEMETSER_PROJECT_LEXER_H

#include <sstream>

#include "../View/IClient.h"
#include "UtilityFunctions.h"
#include "../DefinesAndTypedefs.h"
#include "../Shared_Data/CommandResult.h"

#define RAW_OPEN_SERVER_STR "openDataServer"
#define RAW_CONNECT_TO_SEVER_STR "connect"
#define RAW_CREATE_VARIABLE_STR "var"
#define RAW_BIND_STR "bind"
#define RAW_WHILE_LOOP_STR "while"
#define RAW_PRINT_STR "print"

typedef enum {
    LEXER_PARSE_UNKNOWN_STR = -1,
    LEXER_PARSE_SERVER_OPEN,
    LEXER_PARSE_CONNECT_CLIENT_TO_SERVER,
    LEXER_PARSE_PRINT,
    LEXER_PARSE_CREATE_VARIABLE,
    LEXER_PARSE_START_WHILE_LOOP,
    LEXER_PARSE_BIND_TO
} LexerStringEvaluationResult;

#define FIXED_BUFF_SIZE 1024

class Lexer {
public:
    Lexer(IClient* client) : m_client(client) {};

    ///---------- PUBLIC METHODS ----------
    StringsPairQueue parseLine(ConstStringRef line);
private:
    ///---------- LOCAL VARIABLES ----------
    IClient* m_client;
    bool m_serverAssigned;
    // IServer server;

    /// -------------- PRIVATE METHODS --------------
    // fileLinesToQueue(ConstStringRef fp);

    /// ---- STRING EVALUATIONS ----
    LexerStringEvaluationResult evaluateString(ConstStringRef str);

    /// ----- COMMANDS EXECUTION -----
    void openServer(StringsList::iterator& it);
    void parseBindCommand(StringsList::iterator &it, StringsPairQueue& outQueue);
    void connectClientToServer(StringsList::iterator &it);
    void parseCreateVar(const StringsList& strList, StringsList::iterator &it, StringsPairQueue& outQueue);
    void parseWhileLoopToQueue(StringsList::iterator &it, StringsPairQueue& outQueue);
    void parsePrintCommand(StringsList::iterator &it, StringsPairQueue& outQueue);

    void resultBasedExecution(LexerStringEvaluationResult result,  StringsList strList,
                              StringsList::iterator &it, StringsPairQueue& outQueue);

    /// ----- UTILITY -----
    std::string flushIteratorsContentToString(const StringsList& strList, StringsList::iterator &it);
};


#endif //AP1_SEMETSER_PROJECT_LEXER_H
