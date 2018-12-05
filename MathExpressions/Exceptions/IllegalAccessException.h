//
// Created by alon_vita on 12/5/18.
//

#ifndef MATHUSINGCPP_NOTIMPLEMENTEDERROR_H
#define MATHUSINGCPP_NOTIMPLEMENTEDERROR_H

#include <stdexcept>

class IllegalAccessException : public std::logic_error {
public:
    IllegalAccessException() : std::logic_error("Error: this method belong to an interface, and access to it is denied\n") { };
};

#endif //MATHUSINGCPP_NOTIMPLEMENTEDERROR_H
