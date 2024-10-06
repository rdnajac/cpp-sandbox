#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>
#include <vector>

/**
 * @class Timer
 * @brief A simple timer class to measure execution time of code blocks.
 */
class Timer {
private:
    using TimePoint = std::chrono::high_resolution_clock::time_point; ///< Type for time points.
    using Duration = std::chrono::milliseconds; ///< Type for duration in milliseconds.
    
    TimePoint m_startTime; ///< The start time of the timer.
    std::vector<Duration> m_durations; ///< List of logged durations.
    std::vector<std::string> m_labels; ///< Labels for each logged duration.
    std::vector<long long> m_results; ///< Additional results associated with each log.

public:
    Timer(); ///< Constructor that starts the timer.
    
    void start(); ///< Start or restart the timer.
    
    /**
     * @brief Log the time taken since the last start.
     * @param label Optional label for the logged duration.
     * @param result Optional result associated with the logged time.
     */
    void logTime(const std::string &label = "", long long result = 0);
    
    /**
     * @brief Print all logged time points.
     */
    void printLogs() const;
    
    /**
     * @brief Get the duration of a specific log entry.
     * @param index The index of the log entry.
     * @return Duration in milliseconds.
     */
    long long getDuration(size_t index) const;
    
    /**
     * @brief Print the results associated with each logged time point.
     */
    void printResults() const;
};

#endif // TIMER_HPP
