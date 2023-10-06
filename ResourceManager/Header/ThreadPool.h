#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <unordered_set>
#include <future>

namespace Multi
{
    constexpr int NUM_UNPOLLABLE_THREADS = 2;

    class ThreadPoll
    {
    public:
        static ThreadPoll* getInstance();

        void            startRunningWorkers(int num);
        void            stop();
        void            startMaxPollSize();
        void            addFuncToThread(const std::function<void()>& func);

        ThreadPoll();
        ~ThreadPoll() = default;
    private:

        void workerThread();

        static std::unique_ptr<ThreadPoll>  m_instance;

        int                                 m_maxPoolSize;
        bool                                m_isStop;
        int                                 m_numRunningWorkers;
        std::mutex                          m_task, m_promise;
        std::condition_variable             m_condition;
        std::queue<std::function<void()>>   m_funcsToThread;
        std::vector<std::jthread>           m_workers;
    };
}
