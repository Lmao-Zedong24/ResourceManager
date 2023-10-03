#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <set>

namespace Multi
{
    constexpr int NUM_UNPOLLABLE_THREADS = 2;

    class ThreadPoll
    {
    public:
        static ThreadPoll* getInstance();

        void            startWorkers(int i);
        void            setMaxPollSize();
        void            addFuncToThread(const std::function<void()>& func, int id);
        void            stop();

        int             getPoolId();
        void            waitUntilTasksAreDone(int id);

        ThreadPoll();
        ~ThreadPoll() = default;
    private:

        void workerThread();

        static std::unique_ptr<ThreadPoll>  m_instance;

        int                                 m_maxPoolSize;
        bool                                m_isStop;
        int                                 m_numRunningWorkers;
        std::mutex                          m_task;
        std::mutex                          m_id;
        std::condition_variable             m_condition;
        std::queue<std::function<void()>>   m_funcsToThread;
        std::vector<int>                    m_idNumTaskBuffer;
        //std::queue<std::function<void()>>   m_funcsToThread;
        std::vector<std::jthread>           m_workers;

    };

}
