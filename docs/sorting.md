# Arrays: Sorting and Searching Algorithms

Arrays are fundamental data structures that store elements in contiguous memory locations.
This document covers various sorting and searching algorithms commonly used with arrays.

## Bubble Sort

Bubble Sort is a simple sorting algorithm that repeatedly steps through the list,
compares adjacent elements and swaps them if they are in the wrong order.

```cpp
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}
```

Time Complexity: O(n^2)

## Selection Sort

Selection Sort divides the input list into two parts: a sorted portion at the
left end and an unsorted portion at the right end. It repeatedly selects the
smallest element from the unsorted portion and moves it to the sorted portion.

```cpp
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}
```

Time Complexity: O(n^2)

## Insertion Sort

Insertion Sort builds the final sorted array one item at a time.
It iterates through an input array and removes one element per iteration,
finds the location it belongs within the sorted list, and inserts it there.

```cpp
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}
```

Time Complexity: O(n^2)

## Quick Sort

Quick Sort is a divide-and-conquer algorithm. It works by selecting a 'pivot'
element from the array and partitioning the other elements into two sub-arrays,
according to whether they are less than or greater than the pivot.

```cpp
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
```

Time Complexity: O(n log n) average case, O(n^2) worst case

## Counting Sort

Counting Sort is an integer sorting algorithm that operates by counting the
number of objects that possess distinct key values, and applying prefix sum on
those counts to determine the positions of each key value in the output sequence.

```cpp
void countingSort(int arr[], int n) {
    int output[n];
    int max = *max_element(arr, arr + n);
    int count[max + 1] = {0};

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
```

Time Complexity: O(n + k), where k is the range of input

## Radix Sort

Radix Sort is a non-comparative integer sorting algorithm that sorts data with
integer keys by grouping keys by the individual digits which share the same
significant position and value.

```cpp
void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = *max_element(arr, arr + n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
```

Time Complexity: O(d \* (n + k)), where d is the number of digits and k is the range of each digit

## Merge Sort

Merge Sort is a divide-and-conquer algorithm that divides the input array into
two halves, recursively sorts them, and then merges the two sorted halves.

```cpp
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```

Time Complexity: O(n log n)

## Linear Search

Linear Search is the simplest search algorithm that searches for an element in an array by sequentially checking each element until a match is found or the end of the array is reached.

```cpp
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (arr[i] == x)
            return i;
    return -1;
}
```

Time Complexity: O(n)

## Binary Search

Binary Search is an efficient algorithm for searching a sorted array by repeatedly dividing the search interval in half.

```cpp
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}
```

Time Complexity: O(log n)
