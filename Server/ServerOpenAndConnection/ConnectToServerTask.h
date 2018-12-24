//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONNECTTOSERVERTASK_H
#define AP1_SEMETSER_PROJECT_CONNECTTOSERVERTASK_H

#include <condition_variable>

#include "../ThreadPool/Task.h"
#include "../../View/IClient.h"
#include "../../Shared_Data/CommandData.h"

class ConnectToServerTask {
public:
    ConnectToServerTask(CommandDataQueue& commandDataQueue, IClient* client, bool serverRunningStatus) :
    m_client(client), m_commandDataQueue(commandDataQueue), m_serverRunningStatus(serverRunningStatus) {};

    bool run();

private:
    IClient* m_client;
    bool m_serverRunningStatus;
    CommandDataQueue& m_commandDataQueue;
};


#endif //AP1_SEMETSER_PROJECT_CONNECTTOSERVERTASK_H
