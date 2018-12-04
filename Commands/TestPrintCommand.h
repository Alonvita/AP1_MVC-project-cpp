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
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    explicit TestPrintCommand(string str) : str(str) {};

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    void execute() override { cout << "\n" << "My Command is: " << str << "\n\n"; }
private:
    string str;
};

#endif //AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
