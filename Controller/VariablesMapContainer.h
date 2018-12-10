//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_VARIABLESMAPCONTAINER_H
#define AP1_SEMETSER_PROJECT_VARIABLESMAPCONTAINER_H

#include <map>
#include <string>
#include <iostream>

#include "../DefinesAndTypedefs.h"
#include "Utility/UtilityFunctions.h"

class VariablesMapContainer {
public:
    VariablesMapContainer() { this->m_variablesMap = std::map<std::string, var_data*>(); };
    ~VariablesMapContainer();

    /// ---------- GETTERS & SETTERS ----------
    double getData(const std::string& varName);
    var_data* getVarData(const std::string &str);
    VarDataType getType(const std::string& varName);
    void addToMap(const std::string& varName, var_data*varData);

private:
    std::map<std::string, var_data*> m_variablesMap;
};

#endif //AP1_SEMETSER_PROJECT_VARIABLESMAPCONTAINER_H
