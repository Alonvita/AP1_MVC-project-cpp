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

    auto c = new Client();

    // create a client handler to read lines
    ClientHandler* clientHandler = new ClientHandler();

    // run a new client handling task

    delete(threadPool); // delete the threadPool
    delete(c); // delete the client
}