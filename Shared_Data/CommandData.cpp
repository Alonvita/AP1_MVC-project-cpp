//
// Created by alon on 22/12/18.
//

#include "CommandData.h"

/**
 * Constructor.
 *
 * @param name ConstSTringRef -- a const ref to a string.
 * @param data  -- a const ref to a string.
 */
CommandData::CommandData(ConstStringRef name, ConstStringRef data) : m_name(name), m_commandData(data) {
    // Initialize Queue
    this->m_commandsQueue = std::queue<CommandData*>();
}

/**
 * Destructor.
 */
CommandData::~CommandData() {
    // clear the queue
    while(!m_commandsQueue.empty()) {
        SAFELY_POP_COMMAND_DATA_QUEUE(m_commandsQueue)
    }
}