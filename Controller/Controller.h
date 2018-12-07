//
// Created by alon on 07/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_CONTROLLER_H
#define AP1_SEMETSER_PROJECT_CONTROLLER_H

#include <map>

#include "../Shared_Data/CommandResult.h"
#include "Commands/ICommand.h"

class Controller {
public:
    /// -------- CONSTRUCTORS & DESTRUCTORS --------
    // TODO: Controller should receive a ClientHandler* to the constructor after creating ClientHandler
    Controller();
    ~Controller() { for(std::pair<std::string, ICommand*> p : this->commandsList) { delete p.second;} };

    /// -------- EXECUTION --------

    // TODO: after creating the client, this function should receive IClient* client and not an integer
    CommandResult executeCommand(std::string command, int client);


private:
    std::map<std::string, ICommand*> commandsList;
};


#endif //AP1_SEMETSER_PROJECT_CONTROLLER_H
