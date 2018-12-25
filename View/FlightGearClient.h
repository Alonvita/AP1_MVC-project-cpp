//
// Created by alon on 25/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENT_H
#define AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENT_H


#include "IClient.h"
#include "../Shared_Data/Message.h"
#include "../Shared_Data/Notification.h"
#include "../Shared_Data/CommandResult.h"
#include "../DefinesAndTypedefs.h"

class FlightGearClient : public IClient {
public:
    FlightGearClient(int socketID) : g_socket(socketID) {};

    int  getSocketID() override { return g_socket; };
    bool isConnected() override { return true; };

    std::string readMessage() override {};
    void writeMessage(Message m) override {};
    void disconnect(bool keepConnection) override {};
    void receiveNotification(Notification notif) override {};
    void receiveCommandResult(CommandResult result) override {};
    bool connectToServer(uint16_t port, ConstStringRef ip_address) override {};

private:
    int g_socket;
};


#endif //AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENT_H
