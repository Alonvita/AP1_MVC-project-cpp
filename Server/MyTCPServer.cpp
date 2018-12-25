//
// Created by alon on 23/12/18.
//


#include "MyTCPServer.h"

/**
 * TCPServer(uint16_t port, ThreadPool* threadPool, Controller* controller, Lexer* lexer).
 *
 * @param port uint16_t -- a port
 * @param threadPool ThreadPool* -- a pointer to a ThreadPool.
 * @param controller Controller* -- a pointer to a server controller.
 * @param lexer Lexer* -- a pointer to a lexer.
 * @param readsPerSecond int -- number of reads per second
 * @param lock my_thread_lock -- a thread locker struct.
 */
TCPServer::TCPServer(uint16_t port, Controller* controller,
                     Lexer* lexer, int readsPerSecond, MyThreadLock& lock) : m_lock(lock) {
    // initialize local variables
    m_port = port;
    m_lexer = lexer;
    m_controller = controller;
    m_readsPetSecond = readsPerSecond;
}

/**
 * initSocket().
 */
void TCPServer::initSocket() {
    // initialize server
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&m_serverAddress, 0, sizeof(m_serverAddress));
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serverAddress.sin_port = htons(m_port);
    bind(m_sockfd, (struct sockaddr*) &m_serverAddress, sizeof(m_serverAddress));

    // start listening
    listen(m_sockfd, 5);
}

/**
 * receive().
 */
void TCPServer::receive() {
    // set socketsize
    socklen_t sosize = sizeof(m_clientAddress);

    // accept a client
    m_newsockfd = accept(m_sockfd, (struct sockaddr *) &m_clientAddress, &sosize);

    // create a new client
    IClient *c = new FlightGearClient(m_newsockfd);
    flight_gear_arguments args(m_lexer, c, m_readsPetSecond, m_controller);

    // create a thread for handling the flightGear
    pthread_create(&m_flightGearTaskThread, nullptr, &FlightGearClientHandler::handleClient, &args);

    // lock until notified by the other end of the server
    //  when client operation is terminated for any reason.
    {
        std::mutex* m = m_lock.getMutex();
        std::unique_lock<std::mutex> lk(*m);
        m_lock.getCondVariable().wait(lk);
        lk.unlock();
    }
}

void TCPServer::stop() {
    close(m_sockfd); // close the socket

    // clear the client Handlers vector
    for(IClientHandler* handler : m_clientHandlersContainer) {
        delete(handler);
    }

    m_clientHandlersContainer.clear();
}