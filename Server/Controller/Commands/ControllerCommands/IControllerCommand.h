//
// Created by alon on 24/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ICONTROLLERCOMMAND_H
#define AP1_SEMETSER_PROJECT_ICONTROLLERCOMMAND_H

#include "../../../ICommand.h"

class IControllerCommand : public ICommand {
    /// An empty Interface.
};

typedef std::map<std::string, IControllerCommand*> ControllerCommandsMap;

#endif //AP1_SEMETSER_PROJECT_ICONTROLLERCOMMAND_H
