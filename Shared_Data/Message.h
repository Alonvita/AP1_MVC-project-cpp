//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_MESSAGE_H
#define AP1_SEMETSER_PROJECT_MESSAGE_H

#include <string>

enum MessageType { COMMAND_RESULT, NOTIFICATION };

class Message {
public:
    Message(MessageType type, std::string message) : m_type(type), m_message(std::move(message)) {};

    MessageType getType() { return this->m_type; }
    std::string getMessage() { return this->m_message; };

private:
    MessageType m_type;
    std::string m_message;
};


#endif //AP1_SEMETSER_PROJECT_MESSAGE_H
