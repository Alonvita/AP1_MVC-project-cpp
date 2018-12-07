//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_NOTIFICATION_H
#define AP1_SEMETSER_PROJECT_NOTIFICATION_H

#include <string>

enum NotificationType {
    GAME_STARTED,
    GAME_OVER,
    VARIABLE_CREATED,
    EXPRESSION_CALCULATED
    };

class Notification {
public:
    Notification(NotificationType type, std::string data) : m_type(type), m_data(data) {};
    ~Notification() = default;

    std::string getData() { return this->m_data; }
    NotificationType getType() { return m_type; }

private:
    std::string m_data;
    NotificationType m_type;
};

#endif //AP1_SEMETSER_PROJECT_NOTIFICATION_H
