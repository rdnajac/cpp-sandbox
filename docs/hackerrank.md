# HackerRank Problems

## Height of a Binary Tree

To find the height (max depth) of a binary tree, we can use recursion.
The height of a tree with a single node is 0.

```cpp
int height(Node* root) {
    // return -1 if the root is null
    // this gives the height of a tree with a single node as 0
    if (root == nullptr) return -1;

    return 1 + max(height(root->left), height(root->right));
}
```

## Level Order Traversal

In level-order traversal, nodes are visited level by level from left to right.
This is also known as **_breadth-first_** traversal.

```cpp
void levelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;     // declare a queue of Node pointers
    q.push(root);       // push the root node to the queue

    // while the queue is not empty
    while (!q.empty()) {
        Node* current = q.front();  // get the front element of the queue
        q.pop();                    // then remove the front element

        cout << current->data << " ";

        // push the left and right children of the current node to the queue
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}
```

Following the FIFO (First-In-First-Out) principle, we process the nodes level by
level. We start by pushing the root node to the queue. Then, while the queue is
not empty, we dequeue the front node, print its data, and enqueue its children.

## Balanced Brackets

Given $n$ strings, determine if each string has balanced brackets.

```cpp
bool isBalanced(string s) {
    stack<char> st;     // declare a stack of characters

    // iterate through each character in the string
    for (char c : s) {
        // if the character is an opening bracket, push it to the stack
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            // if the stack is empty, return false
            // this means there is an extra closing bracket
            if (st.empty()) return false;

            // if the character is a closing bracket, check if it matches the top of the stack
            if ((c == ')' && st.top() == '(') ||
                (c == ']' && st.top() == '[') ||
                (c == '}' && st.top() == '{')) {
                st.pop();   // if it matches, pop the top element
            } else {
                return false;   // otherwise, return false
            }
        }
    }

    return st.empty();  // return true if the stack is empty
}
```

## Contacts

Given a list of names and queries, determine the number of names that contain
a given partial query.

```cpp
vector<int> contacts(vector<string> queries) {
    vector<string> names;
    vector<int> result;

    for (const string& query : queries) {
        if (query.substr(0, 3) == "add") {
            string name = query.substr(4);  // Extract the name
            names.push_back(name);          // Add name to the vector
        } else if (query.substr(0, 5) == "find") {
            string prefix = query.substr(6); // Extract the prefix
            int count = 0;

            // Count how many names start with the given prefix
            for (const string& name : names) {
                if (name.find(prefix) == 0) { // Check if name starts with prefix
                    count++;
                }
            }
            result.push_back(count); // Store the count
        }
    }

    return result; // Return the results for find queries
}
```

> [!WARNING]
> This solution is not optimized for time in large datasets. A trie data
> structure can be used to improve the performance of the `contacts` function.

## Running Median

Given a list of integers, find the median after each element is added.

```cpp
vector<double> runningMedian(vector<int> a) {
    vector<double> result;
    priority_queue<int> maxHeap;    // max heap for the smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // min heap for the larger half

    for (int i = 0; i < a.size(); i++) {
        if (maxHeap.empty() || a[i] < maxHeap.top()) {
            maxHeap.push(a[i]);
        } else {
            minHeap.push(a[i]);
        }

        // balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        // calculate the median
        if (maxHeap.size() == minHeap.size())
            result.push_back((maxHeap.top() + minHeap.top()) / 2.0);
        else
            result.push_back(maxHeap.top());
    }

    return result;
}
```

This solution uses two heaps to maintain the smaller and larger halves of the
input list. The max heap stores the smaller half, while the min heap stores the
larger half. The median is calculated based on the sizes of the two heaps.

Alternatively, you can use a balanced binary search tree (e.g., `multiset` in
C++) to maintain the sorted order of the elements. You can solve the running
median problem using a sorted vector, but it generally has worse performance
compared to a heap-based method.

> [!NOTE]
> In C++, a heap is implemented as a priority queue. To create a min heap,
> you can use the default comparator. To create a max heap, you can use the
> `std::less` comparator.

```cpp
#include <vector>
#include <algorithm>

std::vector<double> runningMedian(std::vector<int> a) {
std::vector<double> result;
std::vector<int> sortedVec;

    for (int num : a) {
        // Insert num into the sorted vector
        auto pos = std::lower_bound(sortedVec.begin(), sortedVec.end(), num);
        sortedVec.insert(pos, num);

        // Calculate the median
        int n = sortedVec.size();
        if (n % 2 == 1) {
            // Odd number of elements
            result.push_back(sortedVec[n / 2]);
        } else {
            // Even number of elements
            result.push_back((sortedVec[n / 2 - 1] + sortedVec[n / 2]) / 2.0);
        }
    }

    return result;

}
```

> [!IMPORTANT]
> The heap-based method has a time complexity of $O(\log n)$ per insertion
> and $O(1)$ for median calculation, leading to an overall time complexity
> of $O(n \log n)$ for $n$ insertions while the he sorted vector method has
> a time complexity of $O(n)$ for insertion (due to element shifting) and
> $O(1)$ for median calculation, resulting in an overall time complexity of
> $O(n^2)$ in the worst case for $n$ insertions

## Swap Nodes [Algo] Problem

You are given a binary tree and a series of queries.
The goal is to perform swap operations on the tree based on the depth of its nodes. Specifically, for a given integer $ k $, you need to swap the left and right subtrees of all nodes at depths that are multiples of $ k $.

### Swapping Mechanism

- Swapping subtrees means exchanging the left and right children of a node.
- The depth of the root node is 1. If a parent node is at depth $d$,
  its children are at depth $d + 1$.

### Solution

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

struct Node { int left, right; };

void inOrderTraversal(int index, const std::vector<Node>& tree, std::vector<int>& result) {
    if (index == -1) return;
    inOrderTraversal(tree[index].left, tree, result);
    result.push_back(index + 1); // Store the 1-based index
    inOrderTraversal(tree[index].right, tree, result);
}

void swapAtDepth(Node& node, int depth, int k) {
    if (depth % k == 0) {
        std::swap(node.left, node.right);
    }
}

void swapNodesRec(int index, int depth, const std::vector<Node>& tree, int k) {
    if (index == -1) return;
    swapAtDepth(tree[index], depth, k);
    swapNodesRec(tree[index].left, depth + 1, tree, k);
    swapNodesRec(tree[index].right, depth + 1, tree, k);
}

std::vector<std::vector<int>> swapNodes(std::vector<Node> indexes, std::vector<int> queries) {
    std::vector<std::vector<int>> results;
    for (int k : queries) {
        swapNodesRec(0, 1, indexes, k);
        std::vector<int> inOrderResult;
        inOrderTraversal(0, indexes, inOrderResult);
        results.push_back(inOrderResult);
    }
    return results;
}
```
