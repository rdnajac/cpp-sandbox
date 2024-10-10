#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> balloons) {
    int n = balloons.size();
    int steps = 0;
    while (true) {
        steps += 1;
        vector<int> new_balloons = balloons;
        for (int i = 0; i < n; ++i) {
            int share = balloons[i] / 2;  // Balloons to share
            new_balloons[i] -= share;  // Decrease balloons of current house
            new_balloons[(i + 1) % n] += share;  // Increase balloons of next house
        }
        if (new_balloons == balloons) {
            break;
        }
        balloons = new_balloons;
    }
    return steps;
}

int main() {
    std::vector<int> balloons = {4, 1, 2};
    std::cout << solution(balloons) << std::endl;
    return 0;
}