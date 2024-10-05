# C++ LeetCode Cheat Sheet

## Vectors

```cpp
// reverse a vector
reverse(vec.begin(), vec.end());

// copy with simple assignment
vector<int> vec_copy = vec;

// append a vector to another vector
vec1.insert(vec1.end(), vec2.begin(), vec2.end());

// sort a vector
sort(vec.begin(), vec.end());

// sort a vector of pairs by the first element
sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
});

// Custom comparator
sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });

// binary search
bool found = binary_search(vec.begin(), vec.end(), target);
auto it = lower_bound(vec.begin(), vec.end(), target);
```

## Strings

### Initialization and Basic Operations

```
string s = "hello";
int len = s.length();
char first = s[0];
s += " world";  // Concatenation
```

### Substring

```
string sub = s.substr(start_index, length);
```

### String to Integer and vice versa

```
int num = stoi("123");
string str = to_string(123);
```

## Maps and Sets

### Initialization and Basic Operations

```
unordered_map<int, int> map;
map[key] = value;
if (map.count(key)) { /* key exists */ }

unordered_set<int> set;
set.insert(value);
if (set.count(value)) { /* value exists */ }
```

## Queue and Stack

### Queue

```
queue<int> q;
q.push(1);
int front = q.front();
q.pop();
```

### Stack

```
stack<int> s;
s.push(1);
int top = s.top();
s.pop();
```

## Priority Queue (Heap)

```
// Max heap
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

maxHeap.push(1);
int top = maxHeap.top();
maxHeap.pop();
```

## Linked List

```
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Traversal
while (head != nullptr) {
    // Process head->val
    head = head->next;
}
```

## Tree

```
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

## Useful Algorithms

### Two Pointers

```
int left = 0, right = n - 1;
while (left < right) {
    // Process elements
    left++;
    right--;
}
```

### Sliding Window

```
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

### Depth-First Search (DFS)

```
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

```
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
