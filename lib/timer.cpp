#include "../include/timer.hpp"
#include <iomanip>
#include <iostream>

Timer::Timer() { start(); }

void Timer::start() {
    m_startTime = std::chrono::high_resolution_clock::now();
}

void Timer::logTime(const std::string &label, long long result) {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Duration>(endTime - m_startTime);
    m_durations.push_back(duration);
    m_labels.push_back(label);
    m_results.push_back(result);
    start(); // Reset the timer for the next measurement
}

void Timer::printLogs() const {
    if (m_durations.empty()) {
        std::cout << "No time points logged." << std::endl;
        return;
    }

    std::cout << std::left << std::setw(30) << "Description" << std::setw(20) << "Duration (ms)"
              << std::endl;

    for (size_t i = 0; i < m_durations.size(); ++i) {
        std::cout << std::left << std::setw(30) << m_labels[i] << std::setw(20)
                  << m_durations[i].count() << std::endl;
    }
}

long long Timer::getDuration(size_t index) const {
    if (index >= m_durations.size())
        return 0;
    return m_durations[index].count();
}

void Timer::printResults() const {
    if (m_durations.empty()) {
        std::cout << "No results to print." << std::endl;
        return;
    }

    for (size_t i = 0; i < m_durations.size(); ++i) {
        std::cout << std::left << std::setw(16) << m_results[i] << std::setw(32) << m_labels[i]
                  << m_durations[i].count() << " ms\n";
    }
}
