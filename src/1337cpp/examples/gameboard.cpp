#include <vector>
#include <iostream>

/**
 * Function to find the positions of open cells ('O') that are adjacent
 * to other open cells on the board.
 * 
 * @param board A 2D vector representing the game board with characters 'O' and 'X'.
 * @return A vector of pairs representing the row and column indices of adjacent open cells.
 */
std::vector<std::pair<int, int>> find_adjacent_open_positions(const std::vector<std::vector<char>>& board) {
    std::vector<std::pair<int, int>> positions; // To store the resulting positions

    // Iterate through each cell in the board
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            // Check if the current cell is an open cell ('O')
            if (board[i][j] == 'O') {
                // Check adjacent cells (up, down, left, right)
                if ((i > 0 && board[i - 1][j] == 'O') || // Up
                    (i < board.size() - 1 && board[i + 1][j] == 'O') || // Down
                    (j > 0 && board[i][j - 1] == 'O') || // Left
                    (j < board[0].size() - 1 && board[i][j + 1] == 'O')) { // Right
                    positions.push_back({i, j}); // Store the position if adjacent to another 'O'
                }
            }
        }
    }
    return positions; // Return the list of positions
}

int main() {
    // Example game board with 'O' for open cells and 'X' for blocked cells
    std::vector<std::vector<char>> board = {
        {'X', 'O', 'O', 'X'},
        {'O', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
        {'X', 'O', 'X', 'O'}
    };

    // Find positions of open cells that are adjacent to other open cells
    std::vector<std::pair<int, int>> positions = find_adjacent_open_positions(board);

    // Output the resulting positions
    std::cout << "Positions of adjacent open cells ('O'):\n";
    for (const auto& pos : positions) {
        std::cout << "(" << pos.first << ", " << pos.second << ")" << std::endl;
    }

    return 0;
}

