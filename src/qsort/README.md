# Quicksort

> The `qsort()` function is a modified partition-exchange sort, or quicksort.

```c
#include <stdlib.h>

void
qsort(void *base, size_t nel, size_t width,
    int (*compar)(const void *, const void *));
```

## `compar` function

The `compar` function is a user-supplied function that returns an integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater than the second.

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

## Time complexity

The time complexity of quicksort is O(n log n) on average, but O(n^2) in the
worst case.

The space complexity is O(log n) on average, but O(n) in the worst
case.

## Sorting in C++

The C++ standard library provides a `std::sort()` function that is implemented
using a hybrid sorting algorithm, which often includes quicksort as one of its components.
