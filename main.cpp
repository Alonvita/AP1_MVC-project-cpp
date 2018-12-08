//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "Controller/Commands/TestPrintCommand.h"
#include "Controller/Commands/Variables/Variable.h"
#include "Shared_Data/CommandResult.h"
#include "Controller/Controller.h"
#include "View/Client.h"

using namespace std;

int main() {
    cout << "MAIN\n";


    // TESTING CONTROLLER EXECUTION WITH CREATE VARIABLE COMMAND
    Client client(199);
    Controller controller;

    std::queue<std::string> commandsQueue; // initialize a commands queue
    commandsQueue.push(MAKE_VAR_STR);

    CommandResult cRslt = controller.executeCommand(commandsQueue, &client);

    cout << cRslt.getData();

    // In the future, this will done inside the "CliendHandler"
    do {

        //CommandResult result;

    } while(false);

}