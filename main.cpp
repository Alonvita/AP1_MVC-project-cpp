//
// Created by alon on 04/12/18.
//

#include <iostream>
#include <future>
#include "View/Client.h"
#include "Shared_Data/Lexer.h"
#include "Server/Controller/Controller.h"
#include "Server/ThreadPool/ThreadPool.h"
#include "Server/ClientHandler/ClientHandler.h"
#include "Server/ServerOpenAndConnection/OpenServerTask.h"
#include "Server/ServerOpenAndConnection/ConnectToServerTask.h"

using namespace std;

int main() {
    // Local Variables
    char msg[MAX_PACKET_SIZE];
    bool serverRunningStatus = false;
    auto m_controller = new Controller();
    CommandDataQueue commandsQueue = CommandDataQueue(); // initialize queue

    auto threadPool = new ThreadPool(5); // initialize threadPool

    // c is initialized nullptr so that we can safely send it to the controller and receive the exception
    //  created there.
    auto client = nullptr;

    auto lexer = new Lexer(); // initialzie the lexer

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

        if(commandsQueue.front()->getName() == PRINT_COMMAND_STR) {
            try {
                // create an open server task
                auto openServerTask = new OpenServerTask(commandsQueue, m_controller, client);

                IServer *server = openServerTask->run();

                // task completed -> set server to running
                serverRunningStatus = true;

                std::cout << "Successfully started the server!\n";
            } catch(std::exception& e) {
                std::cout << e.what();
                continue;
            }
        }

        if(commandsQueue.front()->getName() == CONNECT_TO_SERVER_COMMAND_STR) {
            try {
                auto connectToServerTask = new ConnectToServerTask(commandsQueue, client, serverRunningStatus);

                if(connectToServerTask->run())
                    std::cout << "Successfully connected to server!\n";
            } catch(std::exception& e) {
                std::cout << e.what();
                continue;
            }
        }

        // reaching here means that this is an IControllerCommand
        if(!serverRunningStatus) {
            std::cout << "Must start a server before executing commands like this.\n";
            SAFELY_POP_COMMAND_DATA_QUEUE(commandsQueue); // safely remove command from the queue
            continue; // go back to the beggining
        }

        CommandResult result = m_controller->executeCommand(commandsQueue, client);

        // cut connection -> terminate
        if(!result.keepCon())
            break;
    }
}