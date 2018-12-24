//
// Created by alon on 23/12/18.
//

#include <cstring>
#include "TCPServer.h"
#include "../View/Client.h"
#include "ClientHandler/FlightGearClientHandler.h"


/**
 * TCPServer(uint16_t port, ThreadPool* threadPool, Controller* controller, Lexer* lexer).
 *
 * @param port uint16_t -- a port
 * @param threadPool ThreadPool* -- a pointer to a ThreadPool.
 * @param controller Controller* -- a pointer to a server controller.
 * @param lexer Lexer* -- a pointer to a lexer.
 */
TCPServer::TCPServer(uint16_t port, ThreadPool* threadPool, Controller* controller, Lexer* lexer) {
    // initialize local variables
    m_lexer = lexer;
    m_controller = controller;
    m_threadPool = threadPool;
    m_clientHandlersCount = 0;

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

    // send "connected" notification
    c->receiveNotification(Notification(SERVER_DATA_OPENED, "Connected to server\n"));

    // create a new clientHandler for this client.
    //  Ideally there should be a clientHandler Factory, depending on clients type, but I am not sure
    //  that I'll have the time to do this today...
    m_clientHandlersContainer.push_back(new FlightGearClientHandler(m_controller, m_lexer, c));

    // create a new Task for the clientHandler. The task will be executed by the ThreadPool.
    m_threadPool->addTask(m_clientHandlersContainer[m_clientHandlersCount]);
}

void TCPServer::stop() {
    close(m_sockfd); // close the socket

    // clear the client Handlers vector
    for(IClientHandler* handler : m_clientHandlersContainer) {
        delete(handler);
    }

    m_clientHandlersContainer.clear();
}