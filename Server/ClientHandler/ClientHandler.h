//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CLIENTHANDLER_H
#define AP1_SEMETSER_PROJECT_CLIENTHANDLER_H

#include "IClientHandler.h"
#include "../../Shared_Data/Lexer.h"
#include "../ThreadPool/MyThreadLock.h"

class ClientHandler : public IClientHandler {
public:
    ClientHandler(IController* controller, Lexer* lex,
                  IClient* client, MyThreadLock& lock, CommandResult& result) :
                  m_controller(controller), m_lexer(lex), m_client(client),
                  m_lock(lock), m_result(result) {};

    void run() override;
    void showTask() override {};

private:
    Lexer* m_lexer;
    IClient* m_client;
    MyThreadLock& m_lock;
    CommandResult& m_result;
    IController* m_controller;
};


#endif //AP1_SEMETSER_PROJECT_CLIENTHANDLER_H
