//
// Created by alon on 23/12/18.
//

#include "FlightGearClientHandler.h"

void* FlightGearClientHandler::handleClient(void* arguments) {
    // Local Variables
    ssize_t n;
    char msg[MAX_PACKET_SIZE];
    auto args = (flight_gear_arguments*)arguments;

    while(args->client->isConnected()) {
        // receive a message
        n = recv(args->client->getSocketID(), msg, MAX_PACKET_SIZE, 0);

        // check file ended while reading
        if(n == 0) {
            args->client->disconnect(false);
            return nullptr;
        }

        CommandDataQueue commandsQueue; // local variable

        readFlightGearLine(msg, args->lexer, commandsQueue);

        // execute given commands
        CommandResult result = args->controller->executeCommand(commandsQueue, args->client);

        // send command result to client
        args->client->receiveCommandResult(result);

        // clear msg
        memset(msg,'\0', MAX_PACKET_SIZE);
    }

    return nullptr;
}

/**
 *
 * @param msg
 * @param lexer
 * @param outQueue
 */
void FlightGearClientHandler::readFlightGearLine(char* msg, Lexer* lexer, CommandDataQueue& outQueue) {

    StringsVector splitLine;
    splitStringToVector(std::string(msg), ",", splitLine, false);

    // parse the line from lexer
    lexer->parseFlightGearData(splitLine, outQueue);

    std::cout << "YAUZA\n";
}