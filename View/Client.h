//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CLIENT_H
#define AP1_SEMETSER_PROJECT_CLIENT_H


#include "IClient.h"

class Client : public IClient {
public:
    Client(int clientID) : m_id(clientID) {};
    ~Client() = default;

    std::string readMessage() override;
    void writeMessage(Message m) override;
    void receiveNotification(Notification notif) override;
    void receiveCommandResult(CommandResult result) override;

private:
    int m_id;
};


#endif //AP1_SEMETSER_PROJECT_CLIENT_H
