//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARDATA_H
#define AP1_SEMETSER_PROJECT_VARDATA_H

#include <malloc.h>

enum VarDataType {
    NOT_ASSIGNED = - 1,
    DOUBLE,
    BIND,
    BOOL,
    PAIR
};

class VarData {
public:
    VarData() : m_assigned(false), m_data(nullptr), type(NOT_ASSIGNED) {};
    ~VarData();

    void set_data(void *data, VarDataType type);

    VarDataType get_type() { return this->type; }

    void* get_data() { return this->m_data; }

private:
    /// ---------- PRIVATE MEMBERS ----------
    void* m_data;
    bool m_assigned;
    VarDataType type;

    /// ---------- PRIVATE FUNCTIONS ----------
    void set_type(VarDataType type) { this->type = type; }
};


#endif //AP1_SEMETSER_PROJECT_VARDATA_H
