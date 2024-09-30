#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "rng.hpp"
#include "timer.hpp"

int main() {
    const int SIZE = 100'000'000;
    std::vector<int> v;
    RandomNumberGenerator rng;

    std::cout << "Generating random numbers..." << std::endl;
    for (int i = 0; i < SIZE; i++) {
        v.push_back(rng.getRandomNumber());
    }

    Timer timer;
    long long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;

    timer.start();
    for (int i = 0; i < SIZE; i++) {
        sum1 += v[i];
    }
    timer.logTime("C-style for-loop");

    timer.start();
    for (int i = 0; i < v.size(); i++) {
        sum2 += v[i];
    }
    timer.logTime("C-style for-loop (unsigned)");

    timer.start();
    for (int n : v) {
        sum3 += n;
    }
    timer.logTime("ranged for-loop");

    timer.start();
    std::for_each(v.begin(), v.end(), [&sum4](int n) { sum4 += n; });
    timer.logTime("for_each() with a lambda");

    timer.start();
    sum5 = std::accumulate(v.begin(), v.end(), static_cast<long long>(0));
    timer.logTime("std::accumulate()");

    // Print results
    std::cout << std::left << std::setw(16) << sum1 << std::setw(32)
              << " C-style for-loop:" << timer.getDuration(0) << " ms\n"
              << std::setw(16) << sum2 << std::setw(32)
              << " C-style for-loop (unsigned):" << timer.getDuration(1) << " ms\n"
              << std::setw(16) << sum3 << std::setw(32) << " ranged for-loop "
              << timer.getDuration(2) << " ms\n"
              << std::setw(16) << sum4 << std::setw(32) << " for_each() with a lambda"
              << timer.getDuration(3) << " ms\n"
              << std::setw(16) << sum5 << std::setw(32) << " std::accumulate()"
              << timer.getDuration(4) << " ms\n";

    return 0;
}
