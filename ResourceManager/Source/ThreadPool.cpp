#include "ThreadPool.h"
#include <stdlib.h>  

namespace Multi
{
    std::unique_ptr<ThreadPoll> ThreadPoll::m_instance = nullptr;

    ThreadPoll::ThreadPoll() : 
        m_workers(), m_funcsToThread(), m_isStop(false),
        m_numRunningWorkers()
    {
        m_maxPoolSize = std::thread::hardware_concurrency() - NUM_UNPOLLABLE_THREADS;
    }

    ThreadPoll* ThreadPoll::getInstance()
    {
        if (m_instance == nullptr)
            m_instance = std::make_unique<ThreadPoll>();

        return m_instance.get();
    }

    void ThreadPoll::startRunningWorkers(int num)
    {
        {
            std::unique_lock lk(m_task);

            m_workers.resize(std::clamp(num, (int)m_workers.size(), m_maxPoolSize));

            for (int i = m_numRunningWorkers; i < m_workers.size(); i++)
                m_workers[i] = std::jthread(&ThreadPoll::workerThread, this);

            m_isStop = false;
        }
    }

    void ThreadPoll::startMaxPollSize()
    {
        startRunningWorkers(m_maxPoolSize);
    }

    void ThreadPoll::addFuncToThread(const std::function<void()>& func)
    {
        if (m_workers.empty())
            m_workers.push_back(std::jthread(&ThreadPoll::workerThread, this));

        {
            std::unique_lock lk(m_task);
            m_funcsToThread.emplace(func);
            m_condition.notify_one();
        }
    }

    void ThreadPoll::stop()
    {
        {
            std::unique_lock lk(m_task);
            m_isStop = true;
            m_condition.notify_all();
        }

        bool areRunningThreads = true;
        while (areRunningThreads)       //wait till they all close
        {
            std::unique_lock lk(m_task);
            areRunningThreads = m_numRunningWorkers != 0;
        }
    }

    void ThreadPoll::workerThread()
    {
        static auto wait = [this] { return !m_funcsToThread.empty() || m_isStop; };
        while (true)
        {   
            std::function<void()> func;

            {
                std::unique_lock lk(m_task);
                while (!(!m_funcsToThread.empty() || m_isStop))
                    m_condition.wait(lk, wait);

                if (m_isStop)
                    return;

                m_numRunningWorkers++;
                func = m_funcsToThread.front();
                m_funcsToThread.pop();
            }

            func();

            {
                std::unique_lock lk(m_task);
                m_numRunningWorkers--;
            }
        }
    }
};
