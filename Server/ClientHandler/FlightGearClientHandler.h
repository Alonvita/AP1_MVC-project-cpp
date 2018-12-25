//
// Created by alon on 23/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H
#define AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H

#include <cstring>

#include "ClientHandler.h"
#include "../Controller/Controller.h"

struct flight_gear_arguments {
public:
    flight_gear_arguments(Lexer* lexer, IClient* client, int readsPerSecond, Controller* controller) :
        lexer(lexer), client(client), readsPerSecond(readsPerSecond), controller(controller) {};

    Lexer* lexer;
    IClient* client;
    int readsPerSecond;
    Controller* controller;
};

class FlightGearClientHandler {
public:
    static void* handleClient(void* arguments);

private:
    static void readFlightGearLine(char* msg, Lexer* lexer, CommandDataQueue& outQueue);
};


#endif //AP1_SEMETSER_PROJECT_FLIGHTGEARCLIENTHANDLER_H
