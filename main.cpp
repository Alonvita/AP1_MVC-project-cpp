//
// Created by alon on 04/12/18.
//

#include <iostream>
#include <future>
#include "View/UserClient.h"
#include "Shared_Data/Lexer.h"
#include "Server/Controller/Controller.h"
#include "Server/ThreadPool/ThreadPool.h"
#include "Server/ThreadPool/MyThreadLock.h"
#include "Server/ClientHandler/ClientHandler.h"
#include "Server/ServerOpenAndConnection/OpenServer.h"
#include "Server/ServerOpenAndConnection/ConnectToServer.h"
#include "Server/ServerOpenAndConnection/RunServerTask.h"

#define THREADS 30

using namespace std;

void safelyClearQueue(CommandDataQueue& queue);

int main() {
    // Local Variables
    char msg[MAX_PACKET_SIZE];
    MyThreadLock myThreadLock;
    bool serverRunningStatus = false;
    auto m_controller = new Controller();
    CommandResult result = CommandResult(false, EXECUTION_FAILURE, "Not initialized\n", true);
    CommandDataQueue commandsQueue = CommandDataQueue(); // initialize queue

    auto threadPool = new ThreadPool(THREADS); // initialize threadPool

    // c is initialized nullptr so that we can safely send it to the controller and receive the exception
    //  created there.
    auto client = new Client();

    auto lexer = new Lexer(); // initialzie the lexer

    // initialize the client handler
    ClientHandler* handler = nullptr;

    while(true) {
        // read from command line
        if (fgets(msg, MAX_PACKET_SIZE, stdin) == nullptr)
            throw std::runtime_error("End of line reached. Too many chars received\n");

        try {
            // parse line from Lexer
            lexer->parseLine(msg, commandsQueue);
        } catch(std::exception& e) {
            std::cout << e.what();
            continue;
        }

        if(commandsQueue.empty()) {
            std::cout << "Nothing operable received. Enter something else.\n";
            continue;
        }

        if(commandsQueue.front()->getName() == OPEN_SERVER_COMMAND_STR) {
            try {
                // create an open server task
                auto openServerTask =
                        new OpenServer(commandsQueue, threadPool, lexer, m_controller, client, myThreadLock);

                IServer *server = openServerTask->run();

                // task completed -> set server to running
                serverRunningStatus = true;

                auto task = new RunServerTask(server, myThreadLock);

                threadPool->addTask(task);

                std::cout << "Successfully started the server!\n";
            } catch(std::exception& e) {
                std::cout << e.what();
            }
            continue;
        }

        if(commandsQueue.front()->getName() == CONNECT_TO_SERVER_COMMAND_STR) {
            try {
                auto connectToServerTask = new ConnectToServer(commandsQueue, client, serverRunningStatus);

                if(connectToServerTask->run()) {
                    std::cout << "Successfully connected to server!\n";
                    handler = new ClientHandler(m_controller, lexer, client, myThreadLock, result);
                }
            } catch(std::exception& e) {
                std::cout << e.what();
            }
            continue;
        }

        // reaching here means that this is an IControllerCommand
        if(!serverRunningStatus) {
            std::cout << "Must start a server before executing commands like this.\n";
            SAFELY_POP_COMMAND_DATA_QUEUE(commandsQueue); // safely remove command from the queue
            continue; // go back to the beggining
        }

        if(client->isConnected())
            threadPool->addTask(handler);

        if(!result.commandSucceeded())
            safelyClearQueue(commandsQueue);

        // cut connection -> terminate
        if(!result.keepCon())
            break;
    }
}

/**
 * safelyClearQueue(CommandDataQueue& queue).
 *
 * @param queue CommandDataQueue& -- a ref to commands data queue.
 */
void safelyClearQueue(CommandDataQueue& queue) {
    while(!queue.empty())
        SAFELY_POP_COMMAND_DATA_QUEUE(queue)
}