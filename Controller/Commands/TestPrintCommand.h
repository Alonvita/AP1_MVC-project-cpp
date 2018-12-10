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
    explicit TestPrintCommand(std::string str) : m_Str(std::move(str)) {};
    ~TestPrintCommand() override = default;

    /// ---------- VIRTUAL FUNCTIONS IMPLEMENTATION ---------
    CommandResult execute(IClient* sender, const std::string& command, VarData* placeHolder) override {
        cout << "\n" << "My ICommand is: " << m_Str << "\n\n";

        return CommandResult(true, PRINT, "data", true);
    }
private:
    string m_Str;
};

#endif //AP1_SEMETSER_PROJECT_TESTPRINTCOMMAND_H
