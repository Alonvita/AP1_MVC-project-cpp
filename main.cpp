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

    smart_ptr<ICommand> cmdSmrtPtr(new TestPrintCommand("Test one"));
    smart_ptr<ICommand> cmdSmrtPtr2(new TestPrintCommand("Test two"));
    Variable<ICommand> v = cmdSmrtPtr;

    v = cmdSmrtPtr2;
    v = new TestPrintCommand("Test Three");

    CommandResult r = v.get_object().operator->()->execute(nullptr, "NOTHING", nullptr);

    bool keepCom = true;


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