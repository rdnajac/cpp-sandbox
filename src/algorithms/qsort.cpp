#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Partition function
template<typename T>
size_t partition(std::vector<T>& arr, size_t low, size_t high) {
    T pivot = arr[high];
    size_t i = low;

    for (size_t j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

// Quicksort function
template<typename T>
void quickSort(std::vector<T>& arr, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(arr, low, high);

        if (pi > 0) quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print a vector
template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    // Using a random number generator for creating the input vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    std::vector<int> arr(10);
    std::generate(arr.begin(), arr.end(), [&]() { return dis(gen); });

    std::cout << "Unsorted array: ";
    printVector(arr);

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    printVector(arr);

    // Demonstrating with a vector of doubles
    std::vector<double> doubleArr{3.14, 1.41, 2.71, 0.58, 1.73};

    std::cout << "\nUnsorted double array: ";
    printVector(doubleArr);

    quickSort(doubleArr, 0, doubleArr.size() - 1);

    std::cout << "Sorted double array: ";
    printVector(doubleArr);

    return 0;
}
