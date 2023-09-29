#include <vector>
#include <thread>
#include <functional>

namespace Multi
{
    class ThreadPool
    {
    public:
        static ThreadPool* GetInstance();

        void SetPoolSize(int i);

        void SetDeactivateCallback(const std::function<void()>& callBack);

        std::thread* GetThread();

        void DeactivateThread(const std::thread* thread);

    private:
        ThreadPool() : m_pool()
        {}
        ~ThreadPool() = default;

        static std::unique_ptr<ThreadPool> m_instance;

        std::vector<std::thread> m_pool;
        std::vector<bool> m_threadInUseBuffer;
        std::function<void()> m_callBack;
    };

}
