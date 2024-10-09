#include <algorithm>
#include <iostream>
#include <vector>

/*
 * std::find
 */
void find_example() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  // parameters:
  // 1. begin iterator
  // 2. end iterator
  // 3. value to find
  auto it = std::find(v.begin(), v.end(), 3);
  if (it != v.end()) {
    std::cout << "Found: " << *it << std::endl;
  } else {
    std::cout << "Not found" << std::endl;
  }
}
