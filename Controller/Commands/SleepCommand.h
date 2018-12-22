//
// Created by alon on 11/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_SLEEPCOMMAND_H
#define AP1_SEMETSER_PROJECT_SLEEPCOMMAND_H

#include <unistd.h>
#include <sstream>

#include "ICommand.h"

class SleepCommand : public ICommand {
public:
    SleepCommand() = default;
    ~SleepCommand() override = default;

    CommandResult execute(IClient* sender, CommandData command, VarData* placeHolder) override;

};


#endif //AP1_SEMETSER_PROJECT_SLEEPCOMMAND_H
