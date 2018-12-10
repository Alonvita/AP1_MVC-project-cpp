//
// Created by alon on 10/12/18.
//

#include "VarData.h"

VarData::~VarData() {
    if(!m_assigned)
        return;

    if (this->type != BOOL)
        free(this->m_data);
}

/**
 * set_data(void *data, VarDataType type).
 *
 * @param data void* -- a pointer to some data.
 * @param type VarDataType -- enum representing the data type.
 */
void VarData::set_data(void *data, VarDataType type)  {
    if (!m_assigned) {
        m_assigned = true;
        this->m_data = data;
        set_type(type);
        return;
    }

    // taken -> free data and retake value and type
    free(m_data);
    this->m_data = data;
    set_type(type);
}