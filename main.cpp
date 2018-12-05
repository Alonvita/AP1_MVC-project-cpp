//
// Created by alon on 04/12/18.
//



#include <iostream>
#include "Commands/Variables/Variable.h"
#include "Commands/TestPrintCommand.h"

using namespace std;

int main() {
    cout << "MAIN\n";

    LOG(INFO) << "WHAT....\n";

    smart_ptr<Command> cmdSmrtPtr(new TestPrintCommand("Test one"));
    Variable<Command> v = cmdSmrtPtr;

    v.get_object().operator->()->execute();
}