//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_COMMAND_H
#define AP1_SEMETSER_PROJECT_COMMAND_H

#include <queue>
#include <iostream>

#include "../../View/IClient.h"
#include "../../Utility/VarData.h"
#include "../../DefinesAndTypedefs.h"
#include "../../Utility/UtilityFunctions.h"
#include "../../Shared_Data/CommandData.h"

/**
 * Command will serve as a pure-virtual class for commands to inherit.
 *  Commands must be able to execute().
 */

class ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    virtual ~ICommand() = default;

    /// ---------- PURE VIRTUAL METHODS ----------
    virtual CommandResult execute(IClient* sender, CommandData* commandPtr, VarData* inHolder, VarData* outHolder) = 0;
};

typedef std::map<std::string, ICommand*> CommandsMap;
typedef std::pair<std::string, ICommand*> CommandsMapPair;

#endif //AP1_SEMETSER_PROJECT_COMMAND_H