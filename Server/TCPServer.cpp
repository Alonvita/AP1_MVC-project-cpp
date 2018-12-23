//
// Created by alon on 23/12/18.
//

#include <cstring>
#include "TCPServer.h"
#include "../View/Client.h"


/**
 * TCPServer(uint16_t port, ThreadPool* threadPool).
 *
 * @param port uint16_t -- a port
 * @param threadPool ThreadPool* -- a pointer to a ThreadPool.
 */
TCPServer::TCPServer(uint16_t port, ThreadPool* threadPool) {
    // initialize local variables
    m_threadPool = threadPool;
    m_clientHandler;

    // initialize server
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&m_serverAddress, 0, sizeof(m_serverAddress));
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serverAddress.sin_port = htons(port);
    bind(m_sockfd, (struct sockaddr*) &m_serverAddress, sizeof(m_serverAddress));

    // start listening
    listen(m_sockfd, 5);
}

/**
 * receive().
 */
void TCPServer::receive() {
    // set socketsize
    socklen_t  sosize = sizeof(m_clientAddress);

    // accept a client
    m_newsockfd = accept(m_sockfd, (struct sockaddr*)&m_clientAddress, &sosize);

    // create a new client
    IClient* c = new Client(m_newsockfd);

    if(THREADS_NUMBER < m_threadsCounter) {
        c->receiveNotification(Notification(FAILURE, "Sorry, the server is full.\n"));
        return;
    } else {
        c->receiveNotification(Notification(CONNECTED_TO_SERVER, "Successfully connected to server\n"));
    }

    // create a new Task for the clientHandler. The task will be executed by the ThreadPool.
    m_threadPool->addTask(m_clientHandler);
}

void TCPServer::stop() { return; }