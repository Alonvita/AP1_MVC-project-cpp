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

#define FIXED_BUFF_SIZE 1024

class Lexer {
public:
    Lexer(IClient* client) : m_client(client) {};

    ///---------- PUBLIC METHODS ----------
    CommandResult parseLine(ConstStringRef line);
private:
    ///---------- LOCAL VARIABLES ----------
    IClient* m_client;
    bool m_serverAssigned;
    // IServer server;

    ///---------- PRIVATE METHODS ----------
    bool varCommand(ConstStringRef commandStr);
    bool connectCommand(ConstStringRef commandStr);
    bool openServerCommand(ConstStringRef commandStr);
    bool readFromFileCommand(ConstStringRef commandStr);
    bool whileLoopCommand(ConstStringRef commandStr);

    void connectToServer(int port, ConstStringRef ip);
    // fileLinesToQueue(ConstStringRef fp);
    CommandResult openServer(StringsList::iterator& it);
    CommandResult ParseConnectToServer(StringsList::iterator &it);
    StringsPair& parseCreateVarCommand(StringsList::iterator& it);
    StringsPairQueue& parseWhileLoopToQueue(StringsList::iterator& it);
};


#endif //AP1_SEMETSER_PROJECT_LEXER_H
