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

    void ThreadPoll::startWorkers(int i)
    {
        stop();

        {
            std::unique_lock lk(m_task);
            m_workers.resize(std::clamp(i, 0, m_maxPoolSize));

            for (int i = 0; i < m_workers.size(); i++)
                m_workers[i] = std::jthread(&ThreadPoll::workerThread, this);

            m_isStop = false;
        }

    }

    void ThreadPoll::setMaxPollSize()
    {
        startWorkers(m_maxPoolSize);
    }

    void ThreadPoll::addFuncToThread(const std::function<void()>& func, int id = -1)
    {
        if (m_workers.empty())
            m_workers.push_back(std::jthread(&ThreadPoll::workerThread, this));

        {
            std::unique_lock lk(m_task);

            if (id >= 0 && id < m_idNumTaskBuffer.size())
            {
                std::function<void()> newFunc([this, func, id] { func();  m_idNumTaskBuffer[id]--; });
                m_funcsToThread.emplace(newFunc);
                m_idNumTaskBuffer[id]++;
            }
            else
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

    int ThreadPoll::getPoolId()
    {
        m_idNumTaskBuffer.push_back(0);
        return m_idNumTaskBuffer.size() - 1;
    }

    void ThreadPoll::waitUntilTasksAreDone(int id)
    {
        bool areRunningTasks = true;
        while (areRunningTasks)       //wait till they all done
        {
            std::unique_lock lk(m_id);
            areRunningTasks = m_idNumTaskBuffer[id] != 0;
        }
    }

    void ThreadPoll::workerThread()
    {
        while (true)
        {   
            std::function<void()> func;

            {
                std::unique_lock lk(m_task);
                m_condition.wait(lk, [this] { return !m_funcsToThread.empty() || m_isStop; });

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
