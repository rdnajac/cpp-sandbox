# Time Complexity

Time complexity is a measure of the amount of time an algorithm takes to
complete as a function of the size of the input. It is often expressed using
big-O notation, which describes the upper bound of the time taken by an
algorithm as a function of the size of the input.

## Big-O notation

Big-O notation describes the upper bound of the time taken by an algorithm as a
function of the size of the input. It is used to describe the worst-case
performance of an algorithm. For example, an algorithm with a time complexity
of O(n) will take at most n steps to complete, where n is the size of the input.

```c
int sum(int n)
{
    int total = 0;

    for (int i = 1; i <= n; i++) {
        total += i;
    }
    return total;
}
```

The `sum` function has a time complexity of O(n) because it takes at most n
steps to complete, where n is the input to the function.

## Common time complexities

| Notation   | Name              | Example                                                      |
| ---------- | ----------------- | ------------------------------------------------------------ |
| O(1)       | Constant time     | Accessing an element in an array by index (index arithmetic) |
| O(log n)   | Logarithmic time  | Binary search (if the input is sorted)                       |
| O(n)       | Linear time       | Finding the maximum element in an array (one-pass)           |
| O(n log n) | Linearithmic time | Quicksort, mergesort (average case)                          |
| O(n^2)     | Quadratic time    | Bubble sort, selection sort (use of nested loops)            |
| O(2^n)     | Exponential time  | Recursive Fibonacci calculation                              |
| O(n!)      | Factorial time    | Generating all permutations of a set                         |

## Comparing time complexities

The following table shows how the time complexity of different algorithms
compares as the size of the input grows.

| Input size | O(log n) | O(n) | O(n log n) | O(n^2)  | O(2^n)    | O(n!)      |
| ---------- | -------- | ---- | ---------- | ------- | --------- | ---------- |
| 10         | 3        | 10   | 30         | 100     | 1024      | 3628800    |
| 100        | 7        | 100  | 664        | 10000   | 1.27e+30  | 9.33e+157  |
| 1000       | 10       | 1000 | 9965       | 1000000 | 1.07e+301 | 4.02e+2567 |

You get the idea.
