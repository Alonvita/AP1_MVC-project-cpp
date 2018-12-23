//
// Created by alon on 10/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARDATA_H
#define AP1_SEMETSER_PROJECT_VARDATA_H

#include <malloc.h>
#include <iostream>
#include <sstream>

#include "../DefinesAndTypedefs.h"

enum VarDataType {
    NOT_ASSIGNED = - 1,
    DOUBLE,
    BIND,
    BOOL,
    PAIR
};

class VarData {
public:
    explicit VarData(bool data);
    VarData() : m_assigned(false), m_data(nullptr), m_type(NOT_ASSIGNED) {};
    ~VarData();

    VarData& operator=(const VarData& type);

    void        set_data(void *data, VarDataType type);
    VarDataType get_type() const { return m_type; }
    void*       get_data() const { return m_data; }
    bool        get_assigned() const { return m_assigned; }

private:
    /// ---------- PRIVATE MEMBERS ----------
    void* m_data;
    bool m_assigned;
    VarDataType m_type;
    void allocVarDataSpaceFor(void *data);

    /// ---------- PRIVATE FUNCTIONS ----------
    void set_type(VarDataType type) { this->m_type = type; }
};


#endif //AP1_SEMETSER_PROJECT_VARDATA_H
