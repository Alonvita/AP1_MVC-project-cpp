//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CLIENT_H
#define AP1_SEMETSER_PROJECT_CLIENT_H

#include <arpa/inet.h>
#include <cstring>

#include "IClient.h"
#include "../DefinesAndTypedefs.h"

#define EMPTY_ADDRESS ""

class Client : public IClient {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    Client();
    ~Client() = default;

    /// ---------- OVERRIDING INTERFACE FUNCTIONS ----------
    std::string readMessage() override;
    void writeMessage(Message m) override;
    void receiveNotification(Notification notif) override;
    void receiveCommandResult(CommandResult result) override;
    bool connectToServer(int port, ConstStringRef ip_address) override;

    /// ---------- GETTERS & SETTERS ----------
    bool isConnected() override;


private:
    int m_port;
    int g_socket;
    bool m_connected;
    std::string m_ip_address;
    struct sockaddr_in m_connection_details;

    /// ---------- PRIVATE SETTERS ----------
    void setPort(int port);
    void setIPAddress(ConstStringRef ip_address);
};


#endif //AP1_SEMETSER_PROJECT_CLIENT_H
