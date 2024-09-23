#pragma once

#include <chrono>


namespace Testify {
    template<typename ClockType = std::chrono::steady_clock, 
        typename TimePoint = ClockType::time_point>
    class StopWatch {
        using Duration = ClockType::duration;

    public:
        StopWatch() : 
            m_begin(now())
        {}

        Duration Elapsed() {
            return now() - m_begin;
        }

        Duration FetchRestart() {
            auto tmp = m_begin;
            Restart();
            return tmp;
        }

        void Restart() {
            m_begin = now();
        }

    private:
        TimePoint m_begin;
    };
}