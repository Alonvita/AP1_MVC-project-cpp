//
// Created by alon on 11/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_LEXER_H
#define AP1_SEMETSER_PROJECT_LEXER_H

#include <sstream>

#include "CommandData.h"
#include "CommandResult.h"
#include "../View/IClient.h"
#include "../Server/IServer.h"
#include "../Utility/UtilityFunctions.h"
#include "../Utility/GenericFunctions.h"

#define LEXER_SPLIT_DELIMITERS " {}=\"\n"

/**
 * Defines the types of evaluations available by this Lexer.
 */
enum LexerEvalResult {
    LEXER_PARSE_UNKNOWN = -1,
    LEXER_PARSE_PATH,
    LEXER_PARSE_PRINT,
    LEXER_PARSE_ASSIGN,
    LEXER_PARSE_BIND_TO,
    LEXER_PARSE_OPERATOR,
    LEXER_PARSE_IF_COMMAND,
    LEXER_PARSE_SERVER_OPEN,
    LEXER_PARSE_VARIABLE_STR,
    LEXER_PARSE_CLOSE_COMMAND,
    LEXER_PARSE_SLEEP_COMMAND,
    LEXER_PARSE_CREATE_VARIABLE,
    LEXER_PARSE_MATH_EXPRESSION,
    LEXER_PARSE_START_WHILE_LOOP,
    LEXER_PARSE_OPEN_CURLY_BRACKETS,
    LEXER_PARSE_CLOSE_CURLY_BRACKETS,
    LEXER_PARSE_CONNECT_CLIENT_TO_SERVER
};

class Lexer {
public:
    explicit Lexer() : m_closeBracketsCount(0), m_openBracketsCount(0), m_readingSection(false),
        m_readToPlaceHolder(0), m_placeHolder(std::vector<CommandDataVector>()),
        m_curlyBracketsFound(false) {
        m_placeHolder.emplace_back(CommandDataVector());
    };

    ~Lexer() {
        for(CommandDataVector vec : m_placeHolder) {
            for(CommandData* commandDataPtr : vec)
                delete(commandDataPtr);

            vec.clear();
        }
    }

    ///---------- PUBLIC METHODS ----------
    bool doneReadingSection() { return (!m_readingSection); };
    void parseLine(ConstStringRef line, CommandDataQueue& outQueue);

private:
    ///---------- LOCAL VARIABLES ----------
    int m_openBracketsCount;
    int m_readToPlaceHolder;
    bool m_readingSection;
    int m_closeBracketsCount;
    bool m_curlyBracketsFound;
    std::vector<CommandDataVector> m_placeHolder;
    // IServer server;

    /// -------------- PRIVATE METHODS --------------
    void createNewPlaceHolder();
    void assignCommandWithPlaceHolder(CommandData* command);
    void readToPlaceHolderOn() { m_readToPlaceHolder = true; }

    /// ---- STRING EVALUATIONS ----
    LexerEvalResult evaluateString(ConstStringRef str);

    /// ----- COMMANDS EXECUTION -----
    void parseIfCommand(CommandDataVector &outVec);
    void parseSleepCommand(CommandDataVector &outVec);
    void parseWhileLoopToQueue(CommandDataVector &outVec);
    void parseMathExpression(ConstStringRef str, CommandDataVector &outVec);
    void parseCloseCommand(ConstStringRef command, CommandDataVector &outVec);
    void parseOperatorCommand(ConstStringRef str, CommandDataVector &outVector);
    void parseCreateVar(const StringsVector& strVec,int index, CommandDataVector& outVec);
    void parseBindCommand(const StringsVector& strVec, int index, CommandDataVector& outVec);
    void parsePrintCommand(const StringsVector& strVec, int index, CommandDataVector& outVec);
    void parseAssignCommand(const StringsVector& strVec,int index, CommandDataVector& outVec);
    void resultBasedExecution(LexerEvalResult result,  StringsVector& strVec, int listIndex, CommandDataVector& outVec);

    void openServer(const StringsVector &strVec, int index, CommandDataVector &outVec);
    void connectClientToServer(const StringsVector &strVec, int index, CommandDataVector &outVec);
};


#endif //AP1_SEMETSER_PROJECT_LEXER_H
