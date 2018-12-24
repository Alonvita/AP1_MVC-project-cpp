//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_BINDCOMMAND_H
#define AP1_SEMETSER_PROJECT_BINDCOMMAND_H

#include <fcntl.h>
#include <sstream>

#include "IControllerCommand.h"

class BindCommand : public IControllerCommand {
public:
    BindCommand() = default;
    ~BindCommand() override;

    CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) override;
};


#endif //AP1_SEMETSER_PROJECT_BINDCOMMAND_H
