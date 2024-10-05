std::vector<int> solution(const std::vector<int>& numbers) {
    std::vector<int> result;
    std::vector<int> firstpass;

    for (auto i : numbers) {
        if (i % 10 == 0)
            firstpass.push_back(1);
        else
            firstpass.push_back(i + 1);
    }
    std::map<int, int> freq;
    for (auto i : firstpass)
        freq[i]++;
    for (auto i : freq
        result.push_back(i.first * i.second);
    // establish an association between each number and its frequency
    return result;
}

