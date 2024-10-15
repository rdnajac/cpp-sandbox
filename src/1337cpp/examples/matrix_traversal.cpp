#include <iostream>
#include <vector>

std::vector<int> pathTraverse(std::vector<std::vector<int>> &grid, int startRow, int startCol) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Check the validity of the input
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        std::cerr << "Invalid input" << std::endl;
        return {};
    }

    // Define all four possible directions of movement
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    // Start with the value at the starting cell
    std::vector<int> visited = {grid[startRow][startCol]};

    while (true) {
        // Initialize the current maximum as negative one
        int currMax = -1;
        int nextRow = -1, nextCol = -1;

        // Loop over each adjacent cell in all the directions
        for (const auto &dir : directions) {
            // Calculate the new cell's row and column indices
            int newRow = startRow + dir.first;
            int newCol = startCol + dir.second;

            // If the new cell is out of the grid boundary, ignore it
            if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
                continue;
            }

            // If the new cell's value is greater than the current maximum
            if (grid[newRow][newCol] > currMax) {
                // Save it as the next cell to visit
                nextRow = newRow;
                nextCol = newCol;
                currMax = grid[newRow][newCol];
            }
        }

        // If we don't have any valid cell to visit, break from the loop
        if (currMax <= grid[startRow][startCol]) {
            break;
        }

        // Otherwise, go to the next cell
        startRow = nextRow;
        startCol = nextCol;

        // Append the cell's value to the result list
        visited.push_back(currMax);
    }

    // Return the list of visited cells' values
    return visited;
}

int main() {
    std::vector<std::vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<int> res = pathTraverse(grid, 1, 1);
    for (int i = 0; i < res.size(); ++i) {
        std::cout << res[i] << ' ';
    }
    std::cout << std::endl;
    // your code goes here
    return 0;
}

#if 0
#include <iostream>
#include <tuple>
#include <vector>

/**
 * Function to find the next higher adjacent position in the mountain matrix.
 *
 * @param mountain A 2D vector representing the mountain with elevation values.
 * @param current A tuple representing the current position (row, column).
 * @return A tuple with the next higher position or {-1, -1} if no higher position exists.
 */
std::tuple<int, int> pathTraverse(const std::vector<std::vector<int>>& mountain, const std::tuple<int, int>& current) {
    int row = std::get<0>(current);
    int col = std::get<1>(current);
    int currentValue = mountain[row][col];

    // Directions for adjacent cells: up, down, left, right
    std::vector<std::tuple<int, int>> directions = {
        {-1, 0}, // Up
        {1, 0},  // Down
        {0, -1}, // Left
        {0, 1}   // Right
    };

    std::tuple<int, int> nextPosition = {-1, -1}; // Default if no higher position is found

    // Iterate through each direction to find the next higher position
    for (const auto& direction : directions) {
        int newRow = row + std::get<0>(direction);
        int newCol = col + std::get<1>(direction);

        // Check if the new position is within bounds
        if (newRow >= 0 && newRow < mountain.size() && newCol >= 0 && newCol < mountain[0].size()) {
            if (mountain[newRow][newCol] > currentValue) {
                // If found a higher adjacent cell, update nextPosition
                nextPosition = {newRow, newCol};
                break; // Break after finding the first higher position
            }
        }
    }

    return nextPosition; // Return the next higher position or {-1, -1}
}

int main() {
    // Create a matrix named 'mountain' representing ascending values
    std::vector<std::vector<int>> mountain = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Set the starting position on the mountain
    std::tuple<int, int> startingPosition = {1, 1}; // Starting at value 5

    // Call the pathTraverse function to find the next higher position
    std::tuple<int, int> nextStep = pathTraverse(mountain, startingPosition);

    // Output the coordinates of the next step
    if (nextStep == std::make_tuple(-1, -1)) {
        std::cout << "No higher step available from the current position." << std::endl;
    } else {
        std::cout << "Next higher position: (" << std::get<0>(nextStep) << ", " << std::get<1>(nextStep) << ")" << std::endl;
    }

    return 0;
}
#endif
