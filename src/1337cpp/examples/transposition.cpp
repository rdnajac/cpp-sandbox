#include <iostream>
#include <vector>

std::vector<std::vector<int>> transformMatrix(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = rows > 0 ? matrix[0].size() : 0;
    std::vector<std::vector<int>> result(cols, std::vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}


int main() {
    // Initial matrix (2D vector)
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Call our function on the matrix and output the result
    std::vector<std::vector<int>> transposed = transformMatrix(matrix);
    for (const auto& row : transposed) {
        for (int elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
