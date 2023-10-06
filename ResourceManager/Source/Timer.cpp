#include "Timer.h"

namespace Multi
{
    void Timer::Start(int timerLengthMs)
    {
        m_startTime = std::chrono::system_clock::now();
        m_duration = timerLengthMs;
    }

    bool Timer::CheckIfStop()
    {
        auto end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - m_startTime).count() > m_duration;
    }

    void Stopwatch::Start()
    {
        m_startTime = std::chrono::system_clock::now();
    }

    int Stopwatch::Stop()
    {
        auto end = std::chrono::system_clock::now();
        return (int)std::chrono::duration_cast<std::chrono::milliseconds>(end - m_startTime).count();
    }
}
