#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int checkKnightHealth(const std::vector<int>& knights) {
    int nonZeroCount = 0;
    int healthSum = 0;
    int firstNonZeroHealth = 0;

    for (int knight : knights) {
        if (knight > 0) {
            nonZeroCount++;
            healthSum += knight;
            if (firstNonZeroHealth == 0) {
                firstNonZeroHealth = knight;
            } else if (knight != firstNonZeroHealth) {
                return 0; // Found different non-zero health, continue tournament
            }
        }
    }

    if (nonZeroCount == 0) {
        return -1; // All knights have zero health, continue tournament
    } else if (nonZeroCount == 1) {
        return 0; // Only one knight with health, end tournament
    } else if (healthSum == nonZeroCount * firstNonZeroHealth) {
        return 1; // All have same health, end tournament
    }

    return 0; // Should not reach here, but included for completeness
}

void removeDefeatedKnights(std::vector<int>& knights) {
    knights.erase(std::remove_if(knights.begin(), knights.end(), [](int knight) { return knight <= 0; }), knights.end());
}

int tournament(std::vector<int> knights) {
    int rounds = 0; // Start from 0
    while (true) {
        auto tmp = knights;
        // Each knight fights the knight on his right side by subtracting the strength of his opponent from his own
        for (size_t i = 0; i < tmp.size(); ++i) {
            tmp[i] -= knights[(i + 1) % knights.size()];
        }
        removeDefeatedKnights(tmp);
        // Check the health of the knights
        if (checkKnightHealth(tmp)) {
            break;
        }
        knights = tmp; // Update knights with the new strengths
        rounds++;
    }
    return rounds;
}
