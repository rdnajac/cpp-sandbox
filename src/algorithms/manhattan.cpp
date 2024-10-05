#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
using namespace std;

int manhattanDistance(const std::vector<int>& a, const std::vector<int>& b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0, 
                              std::plus<>(), [](int x, int y) { return std::abs(x - y); });
}

// doing this without the stl anb using c looks like this

int convertarraytoconcatint(const std::vector<int>& a) {
    int result = 0;
    for (int x : a) {
        result = result * 10 + x;
    }
    return result;
}

std::pair<std::vector<int>, int> solution(const std::vector<int>& array1, const std::vector<int>& array2) {
    int n = array1.size();
    std::vector<int> rotated = array1;
    int min_distance = std::numeric_limits<int>::max();
    int min_rotation = 0;

    for (int i = 0; i < n; i++) {
        int distance = manhattanDistance(rotated, array2);
        if (distance < min_distance) {
            min_distance = distance;
            min_rotation = i;
        } else if (distance == min_distance) {
            if (convertarraytoconcatint(rotated) > convertarraytoconcatint(array1)) {
                min_rotation = i;
            }
        }
        std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
    }

    // Apply the best rotation
    std::rotate(rotated.begin(), rotated.begin() + min_rotation, rotated.end());
    return std::make_pair(rotated, min_distance);
}

int main() {
    std::vector<int> array1 = {1, 2, 3, 4, 5};
    std::vector<int> array2 = {3, 4, 5, 1, 2};
    auto [rotated, distance] = solution(array1, array2);
    for (int x : rotated) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    std::cout << "Manhattan distance: " << distance << '\n';
    return 0;
}
