#include <iostream>
#include <vector>

std::vector<std::pair<int,int>> solution(std::vector<int> vec1, std::vector<int> vec2) {
    std::vector<std::pair<int,int>> result;
    for(auto i : vec1){
        for(auto j : vec2){
            if(i < j){
                result.push_back({i, j});
            }
        }
    }
    return result;
}

int main() {
    std::vector<int> vec1 = {1, 3, 7}, vec2 = {2, 8, 9};
    std::vector<std::pair<int, int>> res = solution(vec1, vec2);
    for (auto i : res) {
        std::cout << i.first << ' ' << i.second << std::endl;
    }
    return 0;
}