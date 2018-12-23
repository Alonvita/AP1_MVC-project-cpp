//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ICONTROLLER_H
#define AP1_SEMETSER_PROJECT_ICONTROLLER_H

#include "../View/IClient.h"
#include "../Shared_Data/CommandData.h"
#include "../Shared_Data/CommandResult.h"

class IController {
public:
    virtual ~IController() = default;

    /// -------- EXECUTION --------
    virtual CommandResult executeCommand(const CommandDataQueue& commandsQueue, IClient* sender) = 0;
};

#endif //AP1_SEMETSER_PROJECT_ICONTROLLER_H
