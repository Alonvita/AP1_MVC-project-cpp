//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <string>
#include <fstream>

enum ReadWrite {
    READ,
    WRITE,
    UNKOWN
};

template<typename T, typename P> T remove_if(T beg, T end, P pred);
double read_write(std::string file_path, double value = 0, ReadWrite operation);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
