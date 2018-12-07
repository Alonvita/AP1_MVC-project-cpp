//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ICLIENT_H
#define AP1_SEMETSER_PROJECT_ICLIENT_H

#include <iostream>

#include "../Shared_Data/Message.h"
#include "../Shared_Data/CommandResult.h"
#include "../Shared_Data/Notification.h"

/*
 * Clients Interface
 */
class IClient {
    virtual std::string readMessage() = 0;
    virtual void writeMessage(Message m) = 0;
    virtual void receiveNotification(Notification notif) = 0;
    virtual void receiveCommandResult(CommandResult result) = 0;

};
#endif //AP1_SEMETSER_PROJECT_ICLIENT_H
