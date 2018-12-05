//
// Created by alon_vita on 12/5/18.
//

#ifndef MATHUSINGCPP_NOTIMPLEMENTEDERROR_H
#define MATHUSINGCPP_NOTIMPLEMENTEDERROR_H

#include <stdexcept>

class IllegalAccess : public std::logic_error {
public:
    IllegalAccess() : std::logic_error("Error: Function not yet implemented\n") { };
};

#endif //MATHUSINGCPP_NOTIMPLEMENTEDERROR_H
