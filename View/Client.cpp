//
// Created by alon on 07/12/18.
//

#include "Client.h"

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