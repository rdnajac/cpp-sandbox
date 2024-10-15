# Data Structures

Understanding these data structures is crucial for efficient algorithm design and problem-solving.
Each structure has its strengths and ideal use cases.

## Quick Reference

| Data Structure     | Insert              | Delete              | Search              | Space  | Description                 | Important Notes                                    |
| ------------------ | ------------------- | ------------------- | ------------------- | ------ | --------------------------- | -------------------------------------------------- |
| Array              | $O(1)$ or $O(n)$    | $O(n)$              | $O(n)$              | $O(n)$ | Contiguous memory locations | Fast access, fixed size (static arrays)            |
| Dynamic Array      | $O(1)$ amortized    | $O(n)$              | $O(n)$              | $O(n)$ | Resizable array             | Occasional $O(n)$ insert due to resizing           |
| Linked List        | $O(1)$              | $O(1)$              | $O(n)$              | $O(n)$ | Chain of nodes              | Efficient insertion/deletion, poor random access   |
| Stack              | $O(1)$              | $O(1)$              | $O(n)$              | $O(n)$ | LIFO structure              | Constant time push/pop operations                  |
| Queue              | $O(1)$              | $O(1)$              | $O(n)$              | $O(n)$ | FIFO structure              | Constant time enqueue/dequeue operations           |
| Hash Table         | $O(1)$ average      | $O(1)$ average      | $O(1)$ average      | $O(n)$ | Key-value pairs             | Potential $O(n)$ worst-case for collisions         |
| Min/Max Heap       | $O(\log n)$         | $O(\log n)$         | $O(n)$              | $O(n)$ | Tree-based structure        | Efficient for priority queues                      |
| Binary Search Tree | $O(\log n)$ average | $O(\log n)$ average | $O(\log n)$ average | $O(n)$ | Ordered binary tree         | Potential $O(n)$ worst-case for unbalanced trees   |
| Red-Black Tree     | $O(\log n)$         | $O(\log n)$         | $O(\log n)$         | $O(n)$ | Self-balancing BST          | Guaranteed $O(\log n)$ operations                  |
| AVL Tree           | $O(\log n)$         | $O(\log n)$         | $O(\log n)$         | $O(n)$ | Strictly balanced BST       | More balanced than Red-Black, but costlier updates |

## Array

- Pros: Fast access, cache-friendly
- Cons: Fixed size (for static arrays), expensive insertion/deletion
- Use when: Fast access is crucial, size is known and fixed

### Dynamic Array (e.g., `std::vector`)

- Pros: Flexible size, still allows fast access
- Cons: Occasional costly resizing operations
- Use when: Size may vary, but random access is still important

## Linked List (e.g., `std::list`)

- Types: Singly linked, doubly linked, circular
- Pros: Efficient insertion/deletion, dynamic size
- Cons: Poor random access, extra memory for pointers
- Use when: Frequent insertions/deletions, size is unknown or changes frequently

## Stack (e.g., `std::stack`)

- LIFO (Last In, First Out) principle
- Operations: push, pop, top
- Use when: Need to track function calls, undo mechanisms, expression evaluation

## Queue (e.g., `std::queue`)

- FIFO (First In, First Out) principle
- Operations: enqueue, dequeue, front
- Use when: Managing tasks, breadth-first search, buffering

## Hash Table (e.g., `std::unordered_map`)

Also called a hash map, it stores key-value pairs based on the hash value of the
key. A clever hashing algorithm can reduce the time complexity of certain problems.

- Pros: Very fast average-case operations
- Cons: Potential for collisions, may require resizing
- Use when: Fast lookups are crucial, keys are hashable

## Heap (e.g., `std::priority_queue`)

A heap is a specialized tree-based data structure that satisfies the heap
property. It is commonly used to implement priority queues, a data structure
that returns the element with the highest (or lowest) priority.

- Types: Min-heap, max-heap
- Pros: Efficient for priority queue operations
- Cons: Not suitable for searching for arbitrary elements
- Use when: Need to repeatedly remove the smallest/largest element

## Trees

A tree is a hierarchical data structure consisting of nodes connected by edges.

### Binary Search Tree (BST)

- Pros: Maintains sorted order, efficient operations when balanced
- Cons: Can become unbalanced, leading to worst-case $O(n)$ operations
- Use when: Need sorted data with fast insertions/deletions

### Red-Black Tree

- Self-balancing BST
- Pros: Guarantees $O(\log n)$ operations, less rigid balance than AVL trees
- Cons: Complex implementation
- Use when: Need guaranteed performance for a mix of operations

### AVL (Adelson-Velsky and Landis) Tree

- Strictly balanced BST
- Pros: More rigidly balanced than Red-Black trees, faster lookups
- Cons: More rotations during insertion/deletion than Red-Black trees
- Use when: Lookups are more frequent than insertions/deletions

## C++ STL Containers and Common Operations

| Container      | Insert           | Delete         | Search             | Notes                         |
| -------------- | ---------------- | -------------- | ------------------ | ----------------------------- |
| vector         | $O(1)$ amortized | $O(n)$         | $O(n)$             | Dynamic array implementation  |
| list           | $O(1)$           | $O(1)$         | $O(n)$             | Doubly linked list            |
| deque          | $O(1)$ amortized | $O(n)$         | $O(n)$             | Double-ended queue            |
| set            | $O(\log n)$      | $O(\log n)$    | $O(\log n)$        | Red-Black Tree implementation |
| multiset       | $O(\log n)$      | $O(\log n)$    | $O(\log n)$        | Allows duplicates             |
| map            | $O(\log n)$      | $O(\log n)$    | $O(\log n)$        | Red-Black Tree implementation |
| unordered_set  | $O(1)$ average   | $O(1)$ average | $O(1)$ average     | Hash table implementation     |
| unordered_map  | $O(1)$ average   | $O(1)$ average | $O(1)$ average     | Hash table implementation     |
| priority_queue | $O(\log n)$      | $O(\log n)$    | $O(1)$ for max/min | Heap implementation           |
| stack          | $O(1)$           | $O(1)$         | N/A                | Adapter container             |
| queue          | $O(1)$           | $O(1)$         | N/A                | Adapter container             |
