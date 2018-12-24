//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H
#define AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H

#include "ClientHandler.h"

class FlightGearClientHandler : public IClientHandler {
public:
    FlightGearClientHandler(IController* controller, Lexer* lex, IClient* client) :
    m_controller(controller), m_lexer(lex), m_client(client) {};

    void run() override;
    void showTask() override {};

private:
    Lexer* m_lexer;
    IClient* m_client;
    IController* m_controller;
};


#endif //AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H
