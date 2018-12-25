//
// Created by alon on 25/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_THREAD_LOCK_H
#define AP1_SEMETSER_PROJECT_THREAD_LOCK_H

#include <condition_variable>

class MyThreadLock {
public:
    bool isLocked() { return m_lock; }
    std::mutex* getMutex() { return &m_mutex; }
    std::condition_variable& getCondVariable() { return m_cv; }

private:
    bool m_lock;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

#endif //AP1_SEMETSER_PROJECT_THREAD_LOCK_H
