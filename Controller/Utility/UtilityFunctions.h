//
// Created by alon on 06/12/18.
//

#ifndef MATHEXPRESSIONS_UTILITYFUNCTIONS_H
#define MATHEXPRESSIONS_UTILITYFUNCTIONS_H

#include <string>
#include <fstream>

enum VarDataType { DOUBLE, BIND };

struct var_data {
private:
    void* data;
    VarDataType type;
public:
    void set_data(void* data) { this->data = data; }
    void set_type(VarDataType type) { this->type = type; }

    VarDataType get_type() { return this->type; }
    void* get_data() { return this->data; }
};

template<typename T, typename P> T remove_if(T beg, T end, P pred);

#endif //MATHEXPRESSIONS_UTILITYFUNCTIONS_H
