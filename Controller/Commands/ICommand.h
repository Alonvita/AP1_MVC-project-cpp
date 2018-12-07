//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_COMMAND_H
#define AP1_SEMETSER_PROJECT_COMMAND_H

/**
 * Command will serve as a pure-virtual class for commands to inherit.
 *  Commands must be able to execute().
 */

class ICommand {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    ICommand() = default;
    virtual ~ICommand() = 0;

    /// ---------- PURE VIRTUAL METHODS ----------
    virtual void execute() = 0;
};

#endif //AP1_SEMETSER_PROJECT_COMMAND_H
