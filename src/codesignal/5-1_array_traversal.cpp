#include <iostream>
#include <climits> // For INT_MIN
#include <vector>

int solution(std::vector<int> arrayA, std::vector<int> arrayB, int sizeA, int sizeB) {
    int indexA = 0;
    int indexB = -1;
    bool in_arrayA = true;
    int max_value = INT_MIN;
    
    while (true) {
        if (in_arrayA) {
            indexB = arrayA[indexA];
            if (arrayB[indexB] > max_value) {
                max_value = arrayB[indexB];
            }
        } else {
            indexA = arrayB[indexB];
            if (indexA == 0) {
                return max_value;
            }
        }
        in_arrayA = !in_arrayA;
    }
}

int main() {
    std::vector<int> arrayA = {2, 4, 3, 1, 6};
    std::vector<int> arrayB = {4, 0, 3, 2, 0};
    int sizeA = arrayA.size();
    int sizeB = arrayB.size();

    std::cout << "Maximum value encountered in arrayB: " << solution(arrayA, arrayB, sizeA, sizeB) << std::endl;

    return 0;
}