//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPENSERVERTASK_H
#define AP1_SEMETSER_PROJECT_OPENSERVERTASK_H

#include "../IServer.h"
#include "../ThreadPool/Task.h"
#include "../../View/IClient.h"
#include "../Controller/Controller.h"

class OpenServerTask {
public:
    OpenServerTask(CommandDataQueue &commandDataQueue,
                   Controller *controller, IClient *client) :
                   m_commandDataQueue(commandDataQueue),
                   m_controller(controller),
                   m_client(client) {};

    IServer* run();

private:
    IClient *m_client;
    Controller *m_controller;
    CommandDataQueue &m_commandDataQueue;
};


#endif //AP1_SEMETSER_PROJECT_OPENSERVERTASK_H
