//
// Created by alon on 04/12/18.
//

#ifndef AP1_SEMETSER_PROJECT_REFERENCECOUNT_H
#define AP1_SEMETSER_PROJECT_REFERENCECOUNT_H

#include <string>
#include <iostream>

using namespace std;

/**
 * ReferenceCount.
 *  A simple class for to manage the number of active smart pointers
 *
 *  Source: https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
 */
class ReferenceCount {
private:
    int m_RefCount{ 0 };

public:
    void Increment() {
        ++m_RefCount;
    }

    int Decrement() {
        return --m_RefCount;
    }

    int GetCount() const {
        return m_RefCount;
    }
};

#endif //AP1_SEMETSER_PROJECT_REFERENCECOUNT_H
