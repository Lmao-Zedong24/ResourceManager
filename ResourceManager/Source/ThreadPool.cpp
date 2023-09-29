#include "ThreadPool.h"

namespace Multi
{
    ThreadPool* ThreadPool::GetInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::make_unique<ThreadPool>();

        return m_instance.get();
    }

    void ThreadPool::SetPoolSize(int i)
    {
        //m_pool.clear();
        m_pool.resize(i);
        m_threadInUseBuffer.resize(i, false);
    }

    void ThreadPool::SetDeactivateCallback(const std::function<void()>& callBack)
    {
        m_callBack = callBack;
    }

    std::thread* ThreadPool::GetThread()
    {
        for (int i = 0; i < m_threadInUseBuffer.size(); i++)
        {
            if (!m_threadInUseBuffer[i])
            {
                m_threadInUseBuffer[i] = true;
                return &m_pool[i];
            }
        }

        return nullptr;
    }

    void ThreadPool::DeactivateThread(const std::thread* thread)
    {
        for (int i = 0; i < m_pool.size(); i++)
        {
            if (&m_pool[i] == thread)
            {
                m_threadInUseBuffer[i] = false;

                if (m_callBack != nullptr)
                    m_callBack();
            }
        }
    }
};
