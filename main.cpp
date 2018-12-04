//
// Created by alon on 04/12/18.
//



#include <iostream>
#include "File_Parsing/Variables/Variable.h"
#include "Commands/TestPrintCommand.h"

using namespace std;

int main() {
    cout << "MAIN\n";

    smart_ptr<Command> cmdSmrtPtr(new TestPrintCommand("Test one"));
    Variable v = cmdSmrtPtr;

    v.execute_command();
}