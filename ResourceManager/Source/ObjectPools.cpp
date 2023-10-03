//#include <vector>
//#include <thread>
//#include <functional>
//
//class ThreadPool
//{
//public:
//    static ThreadPool* GetInstance()
//    {
//        if (m_instance == nullptr)
//            m_instance = std::make_unique<ThreadPool>();
//
//        return m_instance.get();
//    }
//
//    void SetPoolSize(int i)
//    {
//        //m_pool.clear();
//        m_pool.resize(i);
//        m_threadInUseBuffer.resize(i, false);
//    }
//
//    void SetDeactivateCallback(const std::function<void()>& callBack)
//    {
//        m_callBack = callBack;
//    }
//
//    std::thread* GetThread()
//    {
//        for (int i = 0; i < m_threadInUseBuffer.size(); i++)
//        {
//            if (!m_threadInUseBuffer[i])
//            {
//                m_threadInUseBuffer[i] = true;
//                return &m_pool[i];
//            }
//        }
//
//        return nullptr;
//    }
//
//    void DeactivateThread(const std::thread* thread)
//    {
//        for (int i = 0; i < m_pool.size(); i++)
//        {
//            if (&m_pool[i] == thread)
//            {
//                m_threadInUseBuffer[i] = false;
//
//                if (m_callBack != nullptr)
//                    m_callBack();
//            }
//        }
//    }
//
//private:
//    ThreadPool() : m_pool()
//    {}
//
//    static std::unique_ptr<ThreadPool> m_instance;
//
//    std::vector<std::thread> m_pool;
//    std::vector<bool> m_threadInUseBuffer;
//    std::function<void()> m_callBack;
//};
