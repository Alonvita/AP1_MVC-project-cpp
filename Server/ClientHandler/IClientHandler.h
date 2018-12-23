//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ICLIENTHANDLER_H
#define AP1_SEMETSER_PROJECT_ICLIENTHANDLER_H

#include "../../View/IClient.h"
#include "../ThreadPool/Task.h"
#include "../Controller/IController.h"

class IClientHandler : public Task {
public:
    void run() override = 0;
    void showTask() override = 0;
};

#endif //AP1_SEMETSER_PROJECT_ICLIENTHANDLER_H
