//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_TCPSERVER_H
#define AP1_SEMETSER_PROJECT_TCPSERVER_H


#include "IServer.h"
#include "ThreadPool/ThreadPool.h"
#include "ClientHandler/IClientHandler.h"

#define THREADS_NUMBER 2

class TCPServer : public IServer {
public:
    TCPServer(uint16_t port, ThreadPool* threadpool);
    ~TCPServer() override = default;

protected:
    void stop() override;
    void receive() override;

private:
    int m_threadsCounter;
    pthread_t serverThread;
    int m_sockfd, m_newsockfd;
    struct sockaddr_in m_serverAddress;
    struct sockaddr_in m_clientAddress;

    ThreadPool* m_threadPool;
    IClientHandler* m_clientHandler;
};

#endif //AP1_SEMETSER_PROJECT_TCPSERVER_H