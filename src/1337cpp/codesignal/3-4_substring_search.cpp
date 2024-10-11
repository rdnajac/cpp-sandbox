#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> solution(std::vector<std::string> orig_strs,
                                  std::vector<std::string> substrs) {
    std::vector<std::string> result;

    for (size_t i = 0; i < orig_strs.size(); ++i) {
        size_t start_pos = orig_strs[i].find(substrs[i]);
        std::vector<size_t> match_indices;

        while (start_pos != std::string::npos) {
            match_indices.push_back(start_pos);
            start_pos = orig_strs[i].find(substrs[i], start_pos + substrs[i].size());
        }

        std::ostringstream os;
        os << "The substring '" << substrs[i] << "' was found in the original string '"
           << orig_strs[i] << "' at position(s) ";
        for (size_t idx : match_indices)
            os << idx << ", ";
        os.seekp(-2, os.cur); // remove trailing comma and space
        os << ".";
        result.push_back(os.str());
    }

    return result;
}

int main() {
    // Call the function
    std::vector<std::string> result = solution(
        {"HelloWorld", "LearningC++", "GoForBroke", "BackToBasics"}, {"loW", "ear", "o", "Ba"});
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}