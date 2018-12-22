//
// Created by alon on 04/12/18.
//

#include <iostream>
#include "View/Client.h"
#include "Shared_Data/Lexer.h"

using namespace std;

int main() {
    auto c = new Client();
    StringsPairsQueue q;

    Lexer l(c);

    q = l.parseLine("var x = alt + (90 * 15) + 30");

    std::cout << "Queue's commands order is: \n";

    while(!q.empty()) {
        StringsPair p = q.front();

        std:: cout << "First: " << p.first << "\n";
        std:: cout << "Second: " << p.second << "\n";

        q.pop();
    }

    delete(c);
}