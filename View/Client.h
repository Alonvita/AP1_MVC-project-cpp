//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CLIENT_H
#define AP1_SEMETSER_PROJECT_CLIENT_H

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include "IClient.h"
#include "../DefinesAndTypedefs.h"

#define EMPTY_ADDRESS ""

class Client : public IClient {
public:
    /// ---------- CONSTRUCTORS & DESTRUCTORS ----------
    Client() noexcept;
    explicit Client(int socket_id) noexcept;
    ~Client() = default;

    /// ---------- OVERRIDING INTERFACE FUNCTIONS ----------
    std::string     readMessage() override;
    void            writeMessage(Message m) override;
    void            disconnect(bool keepConnection) override;
    void            receiveNotification(Notification notif) override;
    void            receiveCommandResult(CommandResult result) override;
    bool            connectToServer(uint16_t port, ConstStringRef ip_address) override;

    /// ---------- GETTERS & SETTERS ----------
    bool    isConnected() override;
    int     getSocketID() override { return g_socket; }


private:
    int g_socket;
    uint16_t m_port;
    bool m_connected;
    std::string m_ip_address;
    struct sockaddr_in m_connection_details;

    /// ---------- PRIVATE SETTERS ----------
    void setPort(uint16_t port);
    void setIPAddress(ConstStringRef ip_address);
};


#endif //AP1_SEMETSER_PROJECT_CLIENT_H
