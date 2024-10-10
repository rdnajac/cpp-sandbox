#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

std::string time_adder(std::string time, int seconds) {
    std::string item;
    std::stringstream ss(time);
    /*
     * params
     */
    while (std::getline(ss, item, ':')) {
        std::vector<int> time_parts;
        time_parts.push_back(std::stoi(item));
    }

    int seconds_since_start = time_parts[0] * 3600 + time_parts[1] * 60 + time_parts[2];
    int total_seconds = (seconds_since_start + seconds) % (24 * 3600);
    int hours = total_seconds / 3600;
    total_seconds %= 3600;
    int minutes = total_seconds / 60;
    seconds = total_seconds % 60;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    return os.str();
}

/*
 * @brief Add seconds to a vector of time points
 * @param timePoints A vector of strings representing time points in the format "HH:MM:SS"
 * @param seconds The number of seconds to add to each time point
 * @return A vector of strings representing the new time points in the same format
 */
std::vector<std::string>
add_seconds_to_times(const std::vector<std::string>& timePoints, int seconds) {
    std::vector<std::string> result;
    std::vector<int> time_parts;
    std::string item;

    for (auto time : timePoints) {
        std::istringstream iss(time);

        while (std::getline(iss, item, ':')) {
            time_parts.push_back(std::stoi(item));
        }
        // now we have h/m/s in time_parts[0/1/2]
        // now we do time math. 
        // convert to seconds
        const int SECONDS_IN_DAY = 24 * 60 * 60;
        int seconds_since_start = time_parts[0] * 3600 + time_parts[1] * 60 + time_parts[2];
        int total_seconds = (seconds_since_start + seconds) % SECONDS_IN_DAY;
        // convert back to h/m/s and add to resu
        std::ostringstream os;
        os << std::setfill('0') << std::setw(2) << total_seconds / 3600 << ":" << std::setw(2) << (total_seconds % 3600) / 60 << ":" << std::setw(2) << total_seconds % 60;
        result.push_back(os.str());
    }
    return result;
}


/* @brief given three ints, HH, MM, SS, return the number of seconds since midnight
 * @param hours The number of hours since midnight
 * @param minutes The number of minutes since midnight
 * @param seconds The number of seconds since midnight
 * @return The number of seconds since midnight
 */
int seconds_since_midnight(int hours, int minutes, int seconds) {
    return hours * 3600 + minutes * 60 + seconds;
}

/* @brief given a number of seconds, return a string in the format "HH:MM:SS"
 * @param seconds The number of seconds
 * @return A string in the format "HH:MM:SS"
 */
string sec2time(int seconds) {
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
    return os.str();
}

vector<int> time2sec(const string& time) {
    vector<int> time_parts;
    string item;
    std::istringstream iss(time);
    while (std::getline(iss, item, ':')) {
        time_parts.push_back(std::stoi(item));
    }
    return time_parts;
}

int timePeriodLength(const std::string& timePeriod) {
    string t1, t2;
    // split the string into two times HH:MM:SS - HH:MM:SS
    istringstream iss(timePeriod);
    // Use getline to extract the start and end times

    std::getline(iss, t1, '-');
    std::getline(iss, t2);// now we hve two swtings t1 and t2
    // convert the two times to seconds

    // Trim any leading or trailing spaces
    t1.erase(0, t1.find_first_not_of(' '));
    t1.erase(t1.find_last_not_of(' ') + 1);
    t2.erase(0, t2.find_first_not_of(' '));
    t2.erase(t2.find_last_not_of(' ') + 1);

    // split the two times into hours, minutes, and seconds
    vector<int> time_parts1 = time2sec(t1);
    vector<int> time_parts2 = time2sec(t2);
    // calculate the difference
    return abs(seconds_since_midnight(time_parts1[0], time_parts1[1], time_parts1[2]) - seconds_since_midnight(time_parts2[0], time_parts2[1], time_parts2[2])) / 60;
}


d#include <string>
#include <sstream>
#include <iostream>

int timePeriodLength(const std::string& timePeriod) {
    int startHour, startMinute, startSecond, endHour, endMinute, endSecond;
    char dummy;
    std::istringstream iss(timePeriod);
    std::string start, end;
    std::getline(iss, start, '-');
    std::getline(iss, end);

    // Trim spaces
    start.erase(0, start.find_first_not_of(' '));
    start.erase(start.find_last_not_of(' ') + 1);
    end.erase(0, end.find_first_not_of(' '));
    end.erase(end.find_last_not_of(' ') + 1);

    // Parse start time
    std::istringstream(start) >> startHour >> dummy >> startMinute >> dummy >> startSecond;
    // Parse end time
    std::istringstream(end) >> endHour >> dummy >> endMinute >> dummy >> endSecond;

    // Calculate total seconds since midnight for both times
    int startSeconds = startHour * 3600 + startMinute * 60 + startSecond;
    int endSeconds = endHour * 3600 + endMinute * 60 + endSecond;

    // Calculate the difference in minutes
    int diffMinutes = (endSeconds - startSeconds) / 60;

    return diffMinutes;
}
