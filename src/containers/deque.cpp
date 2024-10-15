#include <deque>
#include <iostream>
#include <vector>

using namespace std;

// Function to print maximums of all contiguous subarrays of size k
void printKMax(int arr[], int n, int k) {
    deque<int> dq;         // Deque to store indices of potential maximums
    vector<int> maxValues; // Vector to store the maximums of each subarray

    for (int i = 0; i < n; ++i) {
        // Remove indices that are out of the current window
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // Remove elements that are smaller than the current element
        while (!dq.empty() && arr[dq.back()] < arr[i]) {
            dq.pop_back();
        }

        // Add current index to the deque
        dq.push_back(i);

        // If we have processed at least k elements, record the maximum
        if (i >= k - 1) {
            maxValues.push_back(arr[dq.front()]);
        }
    }

    // Print the maximums for all subarrays of size k
    for (int value : maxValues) {
        cout << value << " ";
    }
    cout << endl; // New line after each test case
}

int main() {
    // Example test cases
    int testCases = 2;

    // First test case
    int arr1[] = {3, 4, 6, 3, 4};
    int k1 = 2;
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Maximums for test case 1: ";
    printKMax(arr1, n1, k1);

    // Second test case
    int arr2[] = {3, 4, 5, 8, 1, 4, 10};
    int k2 = 4;
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Maximums for test case 2: ";
    printKMax(arr2, n2, k2);

    return 0;
}
