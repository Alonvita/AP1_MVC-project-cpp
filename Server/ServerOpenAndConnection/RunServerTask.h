//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_RUNSERVERTASK_H
#define AP1_SEMETSER_PROJECT_RUNSERVERTASK_H

#include "../IServer.h"
#include "../ThreadPool/Task.h"
#include "../ThreadPool/MyThreadLock.h"

class RunServerTask : public Task {
public:
    RunServerTask(IServer* server, MyThreadLock& lock) : m_server(server), m_lock(lock) {};

    void run() override {
        m_server->initSocket();
        m_server->receive();
    };
    void showTask() override {};

private:
    IServer* m_server;
    MyThreadLock& m_lock;
};

#endif //AP1_SEMETSER_PROJECT_RUNSERVERTASK_H