#include "headers.h"
pair<string, vector<char>> round(string s) {
    string result;
    vector<char> removed;
    for (int i = 0; i < s.size(); i += 2) {
        if (i == s.size() - 1) { // last char unpaired
            result.push_back(s[i]);
            break;
        }
        char first = s[i];
        char second = s[i + 1];
        if (first >= second) {
            result.push_back(first);
            removed.push_back(second);
        } else {
            result.push_back(second);
            removed.push_back(first);
        }
    }
    return make_pair(result, removed);
}

// vector<char> round(string s) {
vector<char> solution(string s) {
    vector<char> removed;
    string modifiedstring = s;
    while (true) {
        pair<string, vector<char>> round_result = round(modifiedstring);
        modifiedstring = round_result.first;
        removed.insert(removed.end(), round_result.second.begin(), round_result.second.end());
        if (round_result.first.size() == 1) {
            removed.push_back(modifiedstring[0]);
            break;
        }
    }
    return removed;
}
