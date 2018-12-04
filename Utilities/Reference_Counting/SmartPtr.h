//
// Created by alon on 04/12/18.
//


#ifndef AP1_SEMETSER_PROJECT_SMARTPTR_H
#define AP1_SEMETSER_PROJECT_SMARTPTR_H

#include "ReferenceCount.h"

/**
 * smart_ptr.
 *  Source: https://www.acodersjourney.com/implementing-smart-pointer-using-reference-counting/
 *
 * @tparam T template <typename T> -- a template for type named T.
 */
template <typename T>
class smart_ptr {
private:
    T* m_Object{ nullptr };
    ReferenceCount* m_ReferenceCount{ nullptr };
public:
    smart_ptr()
    {
    }
    //Constructor
    smart_ptr(T* object)
            : m_Object{ object }
            , m_ReferenceCount{ new ReferenceCount() }
    {
        m_ReferenceCount->Increment();
        LOG(INFO) << "Created smart_ptr! Ref count is " << m_ReferenceCount->GetCount();
    }
    //Destructor
    virtual ~smart_ptr()
    {
        if (m_ReferenceCount)
        {
            int decrementedCount = m_ReferenceCount->Decrement();
            LOG(INFO)  << "Destroyed smart_ptr! Ref count is " << decrementedCount;
            if (decrementedCount <= 0)
            {
                delete m_ReferenceCount;
                delete m_Object;
                m_ReferenceCount = nullptr;
                m_Object = nullptr;
            }
        }
    }
    // Copy Constructor
    smart_ptr(const smart_ptr<T>& other) :
            m_Object{ other.m_Object },
            m_ReferenceCount{ other.m_ReferenceCount } {
        m_ReferenceCount->Increment();
        LOG(INFO)  << "Copied smart_ptr! Ref count is "
             << m_ReferenceCount->GetCount();
    }

    // Overloaded Assignment Operator
    smart_ptr<T>& operator=(const smart_ptr<T>& other)
    {
        if (this != &other)
        {
            if (m_ReferenceCount && m_ReferenceCount->Decrement() == 0)
            {
                delete m_ReferenceCount;
                delete m_Object;
            }
            m_Object = other.m_Object;
            m_ReferenceCount = other.m_ReferenceCount;
            m_ReferenceCount->Increment();
        }
        LOG(INFO)  << "Assigning smart_ptr! Ref count is " << m_ReferenceCount->GetCount() << "\n";
        return *this;
    }

    //Dereference operator
    T& operator*() {
        return *m_Object;
    }

    //Member Access operator
    T* operator->() {
        return m_Object;
    }
};


#endif //AP1_SEMETSER_PROJECT_SMARTPTR_H
