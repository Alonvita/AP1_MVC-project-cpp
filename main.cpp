//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "Controller/Commands/TestPrintCommand.h"
#include "Controller/Commands/Variables/Variable.h"
#include "Shared_Data/CommandResult.h"

using namespace std;

int main() {
    cout << "MAIN\n";

    smart_ptr<ICommand> cmdSmrtPtr(new TestPrintCommand("Test one"));
    smart_ptr<ICommand> cmdSmrtPtr2(new TestPrintCommand("Test two"));
    Variable<ICommand> v = cmdSmrtPtr;

    v = cmdSmrtPtr2;
    v = new TestPrintCommand("Test Three");

    v.get_object().operator->()->execute();

    bool keepCom = true;

    // In the future, this will done inside the "CliendHandler"
    do {


        CommandResult result;

    } while(false);

}