//
// Created by alon on 09/12/18.
//


#include "VariablesMapContainer.h"

/// ---------- CONSTRUCTORS & DESTRUCTORS ----------
/**
 * ~VariablesMapContainer().
 */
VariablesMapContainer::~VariablesMapContainer() {
    // clear the map.
    for(std::pair<std::string, VarData*> p : this->m_variablesMap)
        delete(p.second);
}

/**
 * setExistingVar(ConstStringRef str, double val).
 *
 * @param str ConstStrinfRef -- a constant strinf reference.
 * @param val double -- a value to sign the variable to.
 */
void VariablesMapContainer::setExistingVar(ConstStringRef str, void* data, VarDataType type) {
    auto it = m_variablesMap.find(str);

    if(it == m_variablesMap.end())
        throw std::runtime_error("The requested variable does not exist: " + str);

    (*it).second->set_data(data, type);
}

/**
 * addToMap(std::string varName, double value).
 *
 * @param varName ConstStringRef -- a constant reference to a string representing a varialbe name.
 * @param value double -- a value
 */
void VariablesMapContainer::addToMap(ConstStringRef varName, VarData* varData) {
    this->m_variablesMap.insert(make_pair(varName, varData));
}

/**
 * getData(const std::string &varName).
 *
 * @param varName ConstStringRef -- a constant reference to a string representing a variable name.
 * @return the value of the variable.
 */
double VariablesMapContainer::getData(const std::string &varName) {
    return *((double*)this->m_variablesMap.at(varName)->get_data());
}

/**
 *  *getType(const std::string &varName).
 *
 * @param varName ConstStringRef -- a constant reference to a string representing a variable name.
 * @return the type of the variable.
 */
VarDataType VariablesMapContainer::getType(const std::string &varName) {
    return this->m_variablesMap.at(varName)->get_type();
}

/**
 * getIteratorTo(const std::string &str).
 *
 * @param varName ConstStringRef -- a constant reference to a string representing a variable name.
 *
 * @return a pointer to the pair with this key, or nullptr otherwise.
 */
VarData* VariablesMapContainer::getVarData(ConstStringRef str) {
     auto it = this->m_variablesMap.find(str);

     if(it == this->m_variablesMap.end())
         return nullptr;

    return (*it).second;
}