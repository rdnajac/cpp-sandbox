/* @file vectors.cpp
 * @author Ryan David Najac <rdn2108>
 * @brief std::list vs. std::vector vs. std::set comparison
 */

#include "include/rng.hpp"
#include "include/timer.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>

template <typename Container>
void insertOrdered(Container &container, const std::unordered_set<int> &elements, Timer &timer) {
    timer.start();
    for (int n : elements) {
        auto pos = std::lower_bound(container.begin(), container.end(), n);
        container.insert(pos, n);
    }
    timer.logTime("Insert");
}

template <typename Container>
void removeRandom(Container &container, RandomNumberGenerator &rng, Timer &timer) {
    timer.start();
    while (!container.empty()) {
        auto pos = rng.getRandomIndex(container.size());
        auto iter = container.begin();
        std::advance(iter, pos);
        container.erase(iter);
    }
    timer.logTime("Remove");
}

template <>
void removeRandom(std::vector<int> &container, RandomNumberGenerator &rng, Timer &timer) {
    timer.start();
    while (!container.empty()) {
        container.erase(container.begin() + rng.getRandomIndex(container.size()));
    }
    timer.logTime("Remove");
}

void testContainer(const std::string &containerName, const std::unordered_set<int> &elements,
                   RandomNumberGenerator &rng, Timer &timer) {
    if (containerName == "std::list") {
        std::list<int> container;
        insertOrdered(container, elements, timer);
        removeRandom(container, rng, timer);
    } else if (containerName == "std::vector") {
        std::vector<int> container;
        insertOrdered(container, elements, timer);
        removeRandom(container, rng, timer);
    } else if (containerName == "std::set") {
        std::set<int> container;
        timer.start();
        container.insert(elements.begin(), elements.end());
        timer.logTime("Insert");
        removeRandom(container, rng, timer);
    }
    timer.printResults();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <size>" << std::endl;
        return 1;
    }

    const int SIZE = std::atoi(argv[1]);
    RandomNumberGenerator rng;

    // Generate distinct random numbers
    std::unordered_set<int> elements;
    while (elements.size() < SIZE) {
        elements.insert(rng.getRandomNumber());
    }

    std::cout << "Testing with N = " << SIZE << std::endl;

    Timer listTimer, vectorTimer, setTimer;

    std::cout << "\nTesting std::list:" << std::endl;
    testContainer("std::list", elements, rng, listTimer);

    std::cout << "\nTesting std::vector:" << std::endl;
    testContainer("std::vector", elements, rng, vectorTimer);

    std::cout << "\nTesting std::set:" << std::endl;
    testContainer("std::set", elements, rng, setTimer);

    return 0;
}
