//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "View/Client.h"
#include "Shared_Data/Lexer.h"
#include "Server/Controller/Controller.h"
#include "Server/ThreadPool/ThreadPool.h"

using namespace std;

int main() {
    auto c = new Client();
    CommandDataQueue q;

    Lexer l(c);

    //l.parseLine("while alt < 1000 {", q);
    try {
        l.parseLine("openDataServer", q);
    } catch(std::exception& e) {
        std::cout << e.what();
        exit(0);
    }

    std::cout << "Queue's commands order is: \n";

  //  auto controller = new Controller();

//    CommandResult r = controller->executeCommand(q, c);

    while(!q.empty()) {
        CommandData* p = q.front();

        std:: cout << "First: " << p->getName() << "\n";
        std:: cout << "Second: " << p->getData() << "\n";

        SAFELY_POP_COMMAND_DATA_QUEUE(q)
    }


    delete(c);
    //delete(controller);
}