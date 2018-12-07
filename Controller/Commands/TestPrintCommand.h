//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
#define AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H

#include <iostream>
#include "ICommand.h"

using namespace std;

class TestPrintCommand : public ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    explicit TestPrintCommand(string str) : m_Str(str) {};

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    void execute() override { cout << "\n" << "My ICommand is: " << m_Str << "\n\n"; }
private:
    string m_Str;
};

#endif //AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
