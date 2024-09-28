#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>
#include <vector>

class Timer {
private:
    using TimePoint = std::chrono::high_resolution_clock::time_point;
    using Duration = std::chrono::milliseconds;
    TimePoint m_startTime;
    std::vector<Duration> m_durations;
    std::vector<std::string> m_labels;
    std::vector<long long> m_results;

public:
    Timer();
    void start();
    void logTime(const std::string& label = "", long long result = 0);
    void printLogs() const;
    long long getDuration(size_t index) const;
    void printResults() const;
};

#endif // TIMER_HPP
