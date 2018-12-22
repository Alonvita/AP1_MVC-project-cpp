//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "View/Client.h"
#include "Shared_Data/Lexer.h"

using namespace std;

int main() {
    auto c = new Client();
    CommandDataQueue q;

    Lexer l(c);

    l.parseLine("while alt < 1000 {", q);
    l.parseLine("if alt < 20 {", q);
    l.parseLine("print \"altitude too low!\"", q);
    l.parseLine("}", q);
    l.parseLine("var x = bind \"trump\"", q);
    l.parseLine("}", q);

    std::cout << "Queue's commands order is: \n";

    while(!q.empty()) {
        CommandData* p = q.front();

        std:: cout << "First: " << p->getName() << "\n";
        std:: cout << "Second: " << p->getData() << "\n";

        COMMAND_DATA_QUEUE_POP(q)
    }


    delete(c);
}