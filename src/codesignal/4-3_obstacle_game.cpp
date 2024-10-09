#include <iostream>
#include <vector>

int solution(std::vector<int> numbers, int obstacle) {
    int position = 0;
    int moves = 0;
    while (position < numbers.size()){
        if (numbers[position] == obstacle) {
            return position;
        }
        moves++;
        position += numbers[position];
   }
   return moves;
}

int main() {
    std::cout << solution({2, 3, 3, 4, 2, 4}, 4);
    return 0;
}