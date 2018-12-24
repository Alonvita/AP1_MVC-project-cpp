//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "View/Client.h"
#include "Shared_Data/Lexer.h"
#include "Server/Controller/Controller.h"
#include "Server/ThreadPool/ThreadPool.h"
#include "Server/ClientHandler/ClientHandler.h"

using namespace std;

int main() {
    // Local Variables
    bool serverRunning = false;

    auto threadPool = new ThreadPool(5); // initialize threadPool

    auto lexer = new Lexer(); // lexer
    auto controller = new Controller(); // controller
    auto c = new Client(); // a client

    // create a client handler to read lines
    auto clientHandler = new ClientHandler(controller, lexer, c);

    // run a new client handling task
    threadPool->addTask(clientHandler);

    delete(threadPool); // delete the threadPool
    delete(c); // delete the client
    delete(controller);
    delete(lexer);
    delete(clientHandler);
}