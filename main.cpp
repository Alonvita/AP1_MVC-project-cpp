//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "View/Client.h"
#include "Controller/Controller.h"
#include "Shared_Data/CommandResult.h"
#include "Controller/Commands/TestPrintCommand.h"

using namespace std;

int main() {
    cout << "MAIN\n";


    // TESTING CONTROLLER EXECUTION WITH CREATE VARIABLE COMMAND
    Client client(199);
    Controller controller;

    std::queue<pair<std::string, std::string>> commandsQueue; // initialize a commands queue

    std::stringstream ss;

    ss << "a < 50\n";
    ss << ASSIGN_EXISTING_COMMAND_STR << "\n";
    ss << "a a+10";

    commandsQueue.push(make_pair(WHILE_LOOP_COMMAND_STR, ss.str()));

    CommandResult cRslt = controller.executeCommand(commandsQueue, &client);

    cout << cRslt.getData();

    // In the future, this will done inside the "ClientHandler"
    do {

        //CommandResult result;

    } while(false);

}