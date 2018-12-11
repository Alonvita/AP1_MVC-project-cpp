//
// Created by alon on 07/12/18.
//

#include "Client.h"

/**
 * Constructor.
 */
Client::Client() {
    this->m_port = -1;
    this->g_socket = -1;
    this->m_connected = false;
    this->m_ip_address = EMPTY_ADDRESS;
}

/// ---------- GETTERS & SETTERS ----------

bool Client::isConnected() { return this->m_connected; }

void Client::setPort(int port) {
    if (this->m_port != -1)
        throw std::runtime_error("Port already assigned: " + std::to_string(m_port));

    this->m_port = port;
}

/**
 * setIPAddress(const std::string &ip_address).
 *
 * @param ip_address ConstStringRef -- a constant string reference to an IP address;
 */
void Client::setIPAddress(const std::string &ip_address) {
    struct sockaddr_in dummy;

    if(inet_pton(AF_INET, ip_address.c_str(), &(dummy.sin_addr)) == 0)
        throw std::invalid_argument("Invalid IP Address: " + ip_address);

    if(this->m_ip_address.empty())
        throw std::runtime_error("IP Address already assigned: " + m_ip_address);

    this->m_ip_address = ip_address;
}

/// ---------- OVERRIDING INTERFACE VIRTUAL FUNCTIONS ----------
/**
 * readMessage(Message m).
 */
std::string Client::readMessage() {
    // local variable
    std::string message;

    // read client input
    std::getline(std::cin, message);

    return message;
}

/**
 * writeMessage(Message m)
 *
 * @param m Message -- writes a message to the client.
 */
void Client::writeMessage(Message m) {
    std::cout << m.getMessage();
}

/**
 * sendCommandResult(CommandResult result).
 *
 * @param result CommandResult -- a command result.
 */
void Client::receiveCommandResult(CommandResult result) {
    // create a message
    Message msg = Message(COMMAND_RESULT, result.getData());

    // write it
    writeMessage(msg);
}

/**
 * receiveNotification(Notification notif).
 *
 * @param notif Notification -- a notification.
 */
void Client::receiveNotification(Notification notif) {
    // create a message
    Message msg = Message(NOTIFICATION, notif.getData());

    // write it
    writeMessage(msg);
}

/**
 * connectToServer()
 *
 * @return true on successful connection, or false otherwise.
 */
bool Client::connectToServer(int port, ConstStringRef ip_address) {
    try {
        setPort(port);
        setIPAddress(ip_address);
    } catch(std::exception& e) {
        throw(e);
    }

   if(this->m_port == -1)
       throw std::runtime_error("Must initialize port first\n");

    if(this->m_ip_address.empty())
        throw std::runtime_error("must initialize ip_address first\n");

    this->g_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (g_socket >= 0) {
        // Memset the connection details
        memset(&this->m_connection_details, 0, sizeof(this->m_connection_details));
        this->m_connection_details.sin_family = AF_INET;
        this->m_connection_details.sin_addr.s_addr = inet_addr(this->m_ip_address.c_str());
        this->m_connection_details.sin_port = htons(this->m_port);
        // Connect to a server
        if (connect(this->g_socket,
                    (struct sockaddr *) &this->m_connection_details, sizeof(this->m_connection_details)) >= 0)
            std::cout << ">> Successfully opened socket.";
    } else {
        std::cout << ">> Failure: opening socket.";
    }
}