#include "PoolWorkerThread.h"

PoolWorkerThread::PoolWorkerThread(WorkQueue &_work_queue) : work_queue(_work_queue) {}

void PoolWorkerThread::run() {
    while (Task *task = work_queue.nextTask())
        try {
                task->run();
        } catch (std::exception& e) {
            pthread_exit((void*) &e);
        }
}
