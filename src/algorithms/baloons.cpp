#include <vector>
#include <iostream>

using namespace std;

vector<int> update_balloons(vector<int> balloons) {
    vector<int> new_balloons = balloons;
    for (int i = 0; i < n; i++) {
        int share = balloons[i] / 2; // half of the balloons
        new_balloons[i] -= share;
        new_balloons[(i + 1) % n] += share; // loop around
    }
    return new_balloons;
}

int solution(vector<int> balloons) {
    int steps = 0;
    while (true) {
        steps++;
        vector<int> new_balloons;
        new_ballooons = update_balloons(balloons);

        if (new_balloons == balloons) {
            break; // no change
        }
        balloons = new_balloons;
    }
    return steps;
}
