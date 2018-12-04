//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_COMMAND_H
#define AP1_SEMETSER_PROJECT_COMMAND_H

/**
 * Command will serve as a pure-virtual class for commands to inherit.
 *  Commands must be able to execute().
 */

class Command {
public:
    /// ---------- CONSTRUCTOR & DESTRUCTOR ----------
    Command() = default;
    ~Command() = default;

    /// ---------- PURE VIRTUAL METHODS ----------
    virtual void execute() = 0;
};

#endif //AP1_SEMETSER_PROJECT_COMMAND_H
