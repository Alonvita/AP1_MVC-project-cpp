//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
#define AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H

#include <iostream>
#include "Command.h"

using namespace std;

class TestPrintCommand : public Command {
public:
    explicit TestPrintCommand(string str) : str(str) {};

    void execute() { cout << "My Command is: " << str << "\n"; }
private:
    string str;
};

#endif //AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
