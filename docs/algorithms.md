# Algorithms

## Sorting

For a more in-depth look at sorting algorithms, see the
[Sorting Algorithms](sorting.md) page.

### Quick Sort

The C standard library's `qsort` function

> The `qsort()` function is a modified partition-exchange sort, or quicksort.

```c
#include <stdlib.h>

void
qsort(void *base, size_t nel, size_t width,
    int (*compar)(const void *, const void *));
```

#### `compar` function

The `compar` function is a user-supplied function that returns an integer
less than, equal to, or greater than zero if the first argument is
considered to be respectively less than, equal to, or greater than the second.

```c
int compar(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
```

Here, the `compar` function compares dereferenced pointers-to-integers
and returns the difference between the two values. If the difference is
negative, the first argument is considered less than the second. If the
difference is zero, the two arguments are considered equal.

> [!NOTE]
> The time complexity of quicksort is O(n log n) on average, but O(n^2) in the
> worst case. The space complexity is O(log n) on average, but O(n) in the worst case.

### Sorting in C++

The C++ standard library provides a `sort()` function that is implemented using
a hybrid sorting algorithm, which often includes quicksort as one of its components.

## Manhatan Distance

The Manhattan distance between two arrays, `a` and `b`, of size `n`,
is defined by:

$$
D(a, b) = \sum_{i=0}^{n-1} |a_i - b_i|
$$

> [!NOTE]
> This is equivalent to: $ \sum\_{i=1}^{n} |a_i - b_i| $.
> The only difference is that the first one is zero-indexed and the second one
> is one-indexed.

### Function Signature

```cpp
// function to return the manhattan distance
int manhattanDistance(vector<int> a, vector<int> b) {
    int n = a.size();
    int distance = 0;
    for (int i = 0; i < n; i++) {
        distance += abs(a[i] - b[i]);
    }
    return distance;
}
```

### Problem

Given two arrays, each consisting of n non-negative integers,
discover a rotation of array1 that minimizes the Manhattan distance with array2.

```cpp
std::pair<std::vector<int>, int> solution(const std::vector<int>& array1, const std::vector<int>& array2) {
    int n = array1.size();
    int min_distance = manhattanDistance(array1, array2);
    std::vector<int> min_array = array1;
    for (int i = 0; i < n; i++) {
        std::rotate(array1.begin(), array1.begin() + 1, array1.end());
        int distance = manhattanDistance(array1, array2);
        if (distance < min_distance) {
            min_distance = distance;
            min_array = array1;
        }
    }
    return std::make_pair(min_array, min_distance);
}
```

Good try, Ryan, but there are some issues with your solution. The use of const for array1 is causing compilation errors because std::rotate modifies the array in place.

This solution has a time complexity of $O(n^2)$.
It uses `std::rotate` to rotate the array and `manhattanDistance` to calculate
the distance.

```cpp
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

int manhattanDistance(const std::vector<int>& a, const std::vector<int>& b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0,
                              std::plus<>(), [](int x, int y) { return std::abs(x - y); });
}

std::pair<std::vector<int>, int> solution(const std::vector<int>& array1, const std::vector<int>& array2) {
    int n = array1.size();
    std::vector<int> rotated = array1;
    int min_distance = std::numeric_limits<int>::max();
    int min_rotation = 0;

    for (int i = 0; i < n; i++) {
        int distance = manhattanDistance(rotated, array2);
        if (distance < min_distance) {
            min_distance = distance;
            min_rotation = i;
        }
        std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());
    }

    // Apply the best rotation
    std::rotate(rotated.begin(), rotated.begin() + min_rotation, rotated.end());
    return std::make_pair(rotated, min_distance);
}
```

## More Useful Algorithms

### Two Pointers

```cpp
int left = 0, right = n - 1;
while (left < right) {
    // Process elements
    left++;
    right--;
}
```

### Sliding Window

```cpp
int left = 0, right = 0;
while (right < n) {
    // Expand window
    // Process window
    while (condition) {
        // Shrink window
        left++;
    }
    right++;
}
```

## Tree Traversal

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// DFS Traversal
void dfs(TreeNode* root) {
    if (root == nullptr) return;
    // Process root->val
    dfs(root->left);
    dfs(root->right);
}
```

### Depth-First Search (DFS)

```cpp
void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    if (visited[node]) return;
    visited[node] = true;
    // Process node
    for (int neighbor : graph[node]) {
        dfs(graph, neighbor, visited);
    }
}
```

### Breadth-First Search (BFS)

```cpp
void bfs(vector<vector<int>>& graph, int start) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        // Process node
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}
```
