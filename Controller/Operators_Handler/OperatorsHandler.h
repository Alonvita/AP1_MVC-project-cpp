//
// Created by alon on 09/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
#define AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H

#include <list>
#include <string>
#include <sstream>

#include "../VariablesMapContainer.h"
#include "../../Utility/UtilityFunctions.h"

class OperatorsHandler {
public:
    explicit OperatorsHandler(VariablesMapContainer* vMapContainer) : m_vMap(vMapContainer) {};

    bool evaluate_operation(const std::string &str);
    void giveNumericValueOrGetValFromMap(double&, const std::string&);

private:
    VariablesMapContainer* m_vMap;

    bool evaluate(const std::string& operation, double lhs, double rhs);
};


#endif //AP1_SEMETSER_PROJECT_OPERATORSHANDLER_H
