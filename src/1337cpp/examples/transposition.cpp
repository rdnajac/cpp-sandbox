#include <iostream>
#include <vector>

std::vector<std::vector<int>> transposedMatrix(const std::vector<std::vector<int>> &matrix) {
    int rows = matrix.size();
    int cols = rows > 0 ? matrix[0].size() : 0;
    std::vector<std::vector<int>> result(cols, std::vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result[j][i] = matrix[i][j];
}

// transpose over secondary diagonal
// in an NxN matrix, the secondary diagonal is from (0, N-1) to (N-1, 0)
std::vector<std::vector<int>>
reflectOverSecondaryDiagonal(const std::vector<std::vector<int>> &matrix) {
    size_t size = matrix.size();
    std::vector<std::vector<int>> new_matrix(size, std::vector<int>(size, 0));
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; j++)
            new_matrix[i][j] = matrix[size - j - 1][size - i - 1];
    return new_matrix;
}

int main() {
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};

    std::vector<std::vector<int>> transposed = transposedMatrix(matrix);
    for (const auto &row : transposed) {
        for (int elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
