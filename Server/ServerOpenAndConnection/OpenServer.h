//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPENSERVERTASK_H
#define AP1_SEMETSER_PROJECT_OPENSERVERTASK_H

#include "../IServer.h"
#include "../MyTCPServer.h"
#include "../ThreadPool/Task.h"
#include "../../View/IClient.h"
#include "../Controller/Controller.h"

class OpenServer {
public:
    OpenServer(CommandDataQueue &commandDataQueue, ThreadPool* threadPool,
                   Lexer* lexer, Controller *controller, IClient *client, MyThreadLock& lock) :
                   m_commandDataQueue(commandDataQueue),
                   m_controller(controller), m_lexer(lexer),
                   m_client(client), m_threadPool(threadPool), m_lock(lock) {};

    IServer* run();

private:
    Lexer* m_lexer;
    IClient *m_client;
    MyThreadLock& m_lock;
    Controller *m_controller;
    ThreadPool* m_threadPool;
    CommandDataQueue &m_commandDataQueue;
};


#endif //AP1_SEMETSER_PROJECT_OPENSERVERTASK_H
