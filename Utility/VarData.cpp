//
// Created by alon on 10/12/18.
//

#include <cstring>
#include "VarData.h"

VarData::VarData(bool data) {
    m_data = (int*) malloc(sizeof(int));
    *(bool*)m_data = data;
    m_type = BOOL;
    m_assigned = true;

}

VarData::~VarData() {
    if(m_data == nullptr)
        return;

    free(m_data);
    m_data = nullptr;
    m_assigned = false;
    m_type = NOT_ASSIGNED;
}

/**
 * operator=(const VarData& varData).
 *
 * @param varData const VarData& -- a const ref to another varData.
 */
VarData& VarData::operator=(const VarData& varData) {
    // if already assigned -> free the data
    if(m_assigned) {
        if(m_data != nullptr)
            free(m_data);
    }

    m_type = varData.get_type();
    allocVarDataSpaceFor(varData.get_data());
    m_assigned = varData.get_assigned();
}

/**
 * set_data(void *data, VarDataType type).
 *
 * @param data void* -- a pointer to some data.
 * @param type VarDataType -- enum representing the data type.
 */
void VarData::set_data(void *data, VarDataType type)  {
    set_type(type);
    m_assigned = true;

    if (m_assigned) {
        free(m_data);
    }

    allocVarDataSpaceFor(data);
}

/**
 * allocVarData().
 */
void VarData::allocVarDataSpaceFor(void* data) {

    switch(m_type) {
        case DOUBLE: {
            m_data = (double*) malloc(sizeof(double));
            *(double*)m_data = *(double*)data;

            break;
        }

        case BOOL: {
            m_data = (bool*) malloc(sizeof(bool));
            *(bool*) m_data = *(bool*)data;

            break;
        }

        case BIND: {
            m_data = (char*)malloc(sizeof((char*)data));
            *(char*) m_data = *(char*) data;

            break;
        }

        case PAIR: {
            m_data = (VarDataPair*) malloc(sizeof(((VarDataPair*)data)->first) + sizeof(double));

            strcpy(((VarDataPair*)m_data)->first, (((VarDataPair*)data)->first));
            ((VarDataPair*)m_data)->second = ((VarDataPair*)data)->second;

            break;
        }

        case NOT_ASSIGNED: { return; }
    }

}