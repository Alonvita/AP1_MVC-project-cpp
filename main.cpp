//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "Commands/TestPrintCommand.h"
#include "Commands/Variables/Variable.h"

using namespace std;

int main() {
    cout << "MAIN\n";

    smart_ptr<Command> cmdSmrtPtr(new TestPrintCommand("Test one"));
    smart_ptr<Command> cmdSmrtPtr2(new TestPrintCommand("Test two"));
    Variable<Command> v = cmdSmrtPtr;

    v = cmdSmrtPtr2;
    v = new TestPrintCommand("Test Three");

    v.get_object().operator->()->execute();
}