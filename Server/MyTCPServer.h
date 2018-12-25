//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_TCPSERVER_H
#define AP1_SEMETSER_PROJECT_TCPSERVER_H

#include <cstring>

#include "IServer.h"
#include "../Shared_Data/Lexer.h"
#include "ThreadPool/ThreadPool.h"
#include "Controller/Controller.h"
#include "ThreadPool/MyThreadLock.h"
#include "../View/FlightGearClient.h"
#include "ClientHandler/FlightGearClientHandler.h"

#define THREADS_NUMBER 2

class TCPServer : public IServer {
private:
    uint16_t  m_port;
    int m_sockfd, m_newsockfd;
    struct sockaddr_in m_serverAddress;
    struct sockaddr_in m_clientAddress;

    Lexer* m_lexer;
    MyThreadLock& m_lock;
    int m_readsPetSecond;
    Controller* m_controller;
    pthread_t m_flightGearTaskThread;
    std::vector<IClientHandler*> m_clientHandlersContainer;

public:

    TCPServer(uint16_t port, Controller* controller,
              Lexer* lexer, int readsPerSecond, MyThreadLock& lock);
    ~TCPServer() override = default;

protected:
    void stop() override;
    void receive() override;
    void initSocket() override;
};

#endif //AP1_SEMETSER_PROJECT_TCPSERVER_H
