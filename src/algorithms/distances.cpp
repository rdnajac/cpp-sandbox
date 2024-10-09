#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
#include <cmath>

// Function to compute the Manhattan distance
int manhattanDistance(const std::vector<int>& a, const std::vector<int>& b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0, 
                              std::plus<>(), [](int x, int y) { return std::abs(x - y); });
}

// Function to compute the Hamming distance
int hammingDistance(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same length");
    }
    return std::inner_product(a.begin(), a.end(), b.begin(), 0,
                              std::plus<>(), [](int x, int y) { return x != y ? 1 : 0; });
}

// Function to compute the Euclidean distance
double euclideanDistance(const std::vector<int>& a, const std::vector<int>& b) {
    double sum = std::inner_product(a.begin(), a.end(), b.begin(), 0.0,
                                     std::plus<>(), [](int x, int y) { return std::pow(x - y, 2); });
    return std::sqrt(sum);
}

// Function to find the optimal rotation of array1 to minimize Manhattan distance to array2
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

    // Test Manhattan distance
    auto [rotated, manhattan_dist] = solution(array1, array2);
    std::cout << "Optimal Rotation: ";
    for (int x : rotated) {
        std::cout << x << ' ';
    }
    std::cout << "\nManhattan distance: " << manhattan_dist << '\n';

    // Test Hamming distance
    int hamming_dist = hammingDistance(array1, array2);
    std::cout << "Hamming distance: " << hamming_dist << '\n';

    // Test Euclidean distance
    double euclidean_dist = euclideanDistance(array1, array2);
    std::cout << "Euclidean distance: " << euclidean_dist << '\n';

    return 0;
}
