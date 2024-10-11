#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

std::string time_adder(std::string time, int seconds) {
    std::vector<int> time_parts;
    std::string item;
    std::stringstream ss(time);
    while (std::getline(ss, item, ':')) {
        time_parts.push_back(std::stoi(item));
    }

    int seconds_since_start = time_parts[0] * 3600 + time_parts[1] * 60 + time_parts[2];
    int total_seconds = (seconds_since_start + seconds) % (24 * 3600);
    int hours = total_seconds / 3600;
    total_seconds %= 3600;
    int minutes = total_seconds / 60;
    seconds = total_seconds % 60;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":"
       << std::setw(2) << seconds;
    return os.str();
}

int main() {
    // Call the function
    std::cout << time_adder("05:10:30", 123) << std::endl;
    return 0;
}