#include <iostream>
#include <vector>

std::vector<int> iterateMiddleToEnd(std::vector<int>& numbers) {
    int mid = numbers.size() / 2; // index of the left middle element
    int left, right;
    std::vector<int> newOrder;  // vector to store new order

    if (numbers.size() % 2 == 1) {
        left = mid - 1; // Pointing to the left to the middle element
        right = mid + 1; // Pointing to the right of the middle element
        newOrder.push_back(numbers[mid]); // Adding the middle element to the resulting vector
    }
    else {
        left = mid - 1; // Pointing to the left middle element
        right = mid; // Pointing to the right middle element
    }

    while (left >= 0 && right < numbers.size()) {
        newOrder.push_back(numbers[left--]);
        newOrder.push_back(numbers[right++]);
    }

    return newOrder;
}

std::vector<int> reverse_traverse(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<int> output;

    for (int row = rows - 1; row >= 0; --row) {
        for (int col = cols - 1; col >= 0; --col) {
            output.push_back(matrix[row][col]);
        }
    }

    return output;
}

std::vector<int> counterclockwiseTraversal(std::vector<int>& numbers) {
    

}
