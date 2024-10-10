#include <iostream>
#include <vector>
using namespace std;

int calculate_jump(const vector<int>& forest, int start, int direction) {
    int jump = 1;

    while ((direction * jump) + start >= 0 && (direction * jump) + start < forest.size()) {
        int pos = start;
        while (0 <= pos && pos < forest.size()) {
            if (forest[pos] == 1) {
                break;
            }
            pos += jump * direction;
        }
        if (pos < 0 || pos >= forest.size()) {
            return jump;
        }

        jump += 1;
    }
    return -1;
}

int main() {
    std::vector<int> forest = {0, 1, 0, 0, 0, 0, 1, 1};
    std::cout << calculate_jump(forest, 0, 1) << std::endl;
    return 0;
}