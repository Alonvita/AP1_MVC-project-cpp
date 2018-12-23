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
    for(auto it = this->m_variablesMap.begin(); it != this->m_variablesMap.end(); ++ it) {
        VarData* temp = (*it).second;
        (*it).second = nullptr;

        delete (temp);
    }
}

/**
 * setExistingVar(ConstStringRef str, double val).
 *
 * @param str ConstStrinfRef -- a constant string reference.
 * @param varData const VarData& -- a const ref to a VarData.
 */
void VariablesMapContainer::setExistingVar(ConstStringRef str, VarData& varData) {
    auto it = m_variablesMap.find(str);

    if(it == m_variablesMap.end())
        throw std::runtime_error("The requested variable does not exist: " + str);

    *((*it).second) = varData;
}

/**
 * addToMap(std::string varName, double value).
 *
 * @param varName ConstStringRef -- a constant reference to a string representing a varialbe name.
 * @param value double -- a value
 */
void VariablesMapContainer::addToMap(ConstStringRef varName, VarData* varData) {
    auto it = m_variablesMap.find(varName);

    if(it != m_variablesMap.end())
        throw std::runtime_error("Variable already exists under the name: " + varName + "\n");

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

/**
 *
 * @param varName
 * @return
 */
double VariablesMapContainer::evaluateVariableValueFromMap(const std::string &varName) {
    VarData* vd = this->getVarData(varName);

    // var data does not exist -> throw error
    if(vd == nullptr) {
        std::stringstream ss;
        ss << "Variable " << varName << " does not exist in variables map container.\n";

        throw std::runtime_error(ss.str());
    }

    switch(vd->get_type()) {
        case DOUBLE:
            return *(double*)(vd->get_data());

        case BIND: {
            double value;

            read(*(int*)vd->get_data(), &value, sizeof(double));

            return value;
        }

        case PAIR: {
            return ((VarDataPair*)(vd->get_data()))->second;
        }

        case BOOL: {
            throw std::runtime_error("Error trying to evaluate variable of type double");
        }

        case NOT_ASSIGNED:
            throw std::runtime_error("Variable exists, but is not assigned");
    }
}