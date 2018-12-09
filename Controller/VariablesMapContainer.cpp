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
    for(std::pair<std::string, var_data*> p : this->m_variablesMap)
        free(p.second);
}

/**
 * addToMap(std::string varName, double value).
 *
 * @param varName const std::string& -- a constant reference to a string representing a varialbe name.
 * @param value double -- a value
 */
void VariablesMapContainer::addToMap(const std::string& varName, var_data* varData) {
    this->m_variablesMap.insert(make_pair(varName, varData));
}

/**
 * getData(const std::string &varName).
 *
 * @param varName const std::string& -- a constant reference to a string representing a variable name.
 * @return the value of the variable.
 */
double VariablesMapContainer::getData(const std::string &varName) {
    return *((double*)this->m_variablesMap.at(varName)->get_data());
}

/**
 *  *getType(const std::string &varName).
 *
 * @param varName const std::string& -- a constant reference to a string representing a variable name.
 * @return the type of the variable.
 */
VarDataType VariablesMapContainer::getType(const std::string &varName) {
    return this->m_variablesMap.at(varName)->get_type();
}

/**
 * getIteratorTo(const std::string &str).
 *
 * @param varName const std::string& -- a constant reference to a string representing a variable name.
 *
 * @return a pointer to the pair with this key, or nullptr otherwise.
 */
var_data* VariablesMapContainer::getVarData(const std::string &str) {
     auto it = this->m_variablesMap.find(str);

     if(it == this->m_variablesMap.end())
         return nullptr;

    return (*it).second;
}