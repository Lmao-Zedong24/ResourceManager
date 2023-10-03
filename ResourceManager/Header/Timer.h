#pragma once
#include <chrono>

namespace My
{
    class Timer
    {
    public:
        Timer() : m_duration(0)
        {}

        void Start(int timerLengthMs);
        bool CheckIfStop();

    private:
        std::chrono::time_point<std::chrono::system_clock> m_startTime;
        int  m_duration;
    };

    class Stopwatch
    {
    public:
        Stopwatch() = default;

        void Start();
        int Stop();

    private:
        std::chrono::time_point<std::chrono::system_clock> m_startTime;
    };
}

