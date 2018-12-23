//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_ICLIENT_H
#define AP1_SEMETSER_PROJECT_ICLIENT_H

#include <iostream>
#include <netinet/in.h>

#include "../DefinesAndTypedefs.h"
#include "../Shared_Data/Message.h"
#include "../Shared_Data/CommandResult.h"
#include "../Shared_Data/Notification.h"

/*
 * Clients Interface
 */
class IClient {
public:
    virtual ~IClient() = default;

    virtual int  getSocketID() = 0;
    virtual bool isConnected() = 0;

    virtual std::string readMessage() = 0;
    virtual void writeMessage(Message m) = 0;
    virtual void disconnect(bool keepConnection) = 0;
    virtual void receiveNotification(Notification notif) = 0;
    virtual void receiveCommandResult(CommandResult result) = 0;
    virtual bool connectToServer(uint16_t port, ConstStringRef ip_address) = 0;
};
#endif //AP1_SEMETSER_PROJECT_ICLIENT_H
