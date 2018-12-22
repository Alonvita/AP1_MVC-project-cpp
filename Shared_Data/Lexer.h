//
// Created by alon on 11/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_LEXER_H
#define AP1_SEMETSER_PROJECT_LEXER_H

#include <sstream>

#include "CommandResult.h"
#include "../View/IClient.h"
#include "../Utility/UtilityFunctions.h"
#include "../Utility/GenericFunctions.h"

#define SPLIT_VECTOR_DELIMITERS " {}="
#define SPLIT_OP_STR_LHS_PLACEMENT 0
#define SPLIT_OP_STR_OP_PLACEMENT 1
#define SPLIT_OP_STR_RHS_PLACEMENT 2

/**
 * Defines the types of evaluations available by this Lexer.
 */
enum LexerEvalResult {
    LEXER_PARSE_UNKNOWN = -1,
    LEXER_PARSE_PATH,
    LEXER_PARSE_OPERATOR,
    LEXER_PARSE_VARIABLE_STR,
    LEXER_PARSE_SERVER_OPEN,
    LEXER_PARSE_MATH_EXPRESSION,
    LEXER_PARSE_CONNECT_CLIENT_TO_SERVER,
    LEXER_PARSE_PRINT,
    LEXER_PARSE_ASSIGN,
    LEXER_PARSE_CREATE_VARIABLE,
    LEXER_PARSE_START_WHILE_LOOP,
    LEXER_PARSE_BIND_TO
};

class Lexer {
public:
    explicit Lexer(IClient* client) : m_client(client), m_serverAssigned(false) {};

    ///---------- PUBLIC METHODS ----------
    StringsPairsQueue parseLine(ConstStringRef line);

private:
    ///---------- LOCAL VARIABLES ----------
    IClient* m_client;
    bool m_serverAssigned;
    // IServer server;

    /// -------------- PRIVATE METHODS --------------
    // fileLinesToQueue(ConstStringRef fp);

    /// ---- STRING EVALUATIONS ----
    LexerEvalResult evaluateString(ConstStringRef str);

    /// ----- COMMANDS EXECUTION -----
    void openServer(const StringsVector& strVec, int index);
    void connectClientToServer(const StringsVector& strVec, int index);
    void parseMathExpression(ConstStringRef str, StringsPairsVector &outVec);
    void parseOperatorCommand(ConstStringRef str, StringsPairsVector &outVec);
    void parseIfCommand(const StringsVector& strVec, int index, StringsPairsVector& outVec);
    void parseCloseCommand(const StringsVector& strVec, int index, StringsPairsVector& outVec);
    void parsePrintCommand(const StringsVector& strVec, int index, StringsPairsVector& outVec);
    void parseWhileLoopToQueue(const StringsVector& strVec, int index, StringsPairsVector& outVec);
    void parseBindCommand(const StringsVector& strVec, int index, StringsPairsVector& outVec);
    void parseCreateVar(const StringsVector& strVec,int index, StringsPairsVector& outVec);
    void parseAssignCommand(const StringsVector& strVec,int index, StringsPairsVector& outVec);
    void resultBasedExecution(LexerEvalResult result,  StringsVector strVec, int listIndex, StringsPairsVector& outVec);
};


#endif //AP1_SEMETSER_PROJECT_LEXER_H
