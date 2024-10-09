# Loops in C++

## Loop over half the elements

```cpp
vector<int> some_vector;
for (int i = 0; i < some_vector.size() / 2 + some_vector.size() % 2; i++) {
    // Do something with some_vector[i]
    // including the middle element if the size is odd
}
```

## Iterate over a vector

### `for (const auto &element : vector)`

This uses a reference (`&`) to avoid copying the elements.
The constant qualifier (`const`) ensures that the elements
are not modified. This is the efficient way to iterate over
a vector since no additional memory is allocated.

```cpp
vector<int> some_vector = {1, 2, 3, 4, 5};
for (const auto &element : some_vector) {
    cout << element << endl;
}
```

> [!IMPORTANT]
> The `&` in a variable declaration means that the variable is a reference to
> the object, not a copy of the object itself.

### `for (auto element : vector)`

This creates a copy of each element in the vector. If the
elements are large, this can be inefficient. Use a reference
(`&`) instead to avoid copying.

### `for (auto &element : vector)`

This allows you to modify the elements of the vector.

```cpp
vector<int> some_vector = {1, 2, 3, 4, 5};
for (auto &element : some_vector) {
    element *= 2;
}
cout << "Doubled vector: "; // 2 4 6 8 10
```

> [!NOTE]
> even

### `for (auto it = vector.begin(); it != vector.end(); it++)`

This is the traditional way to iterate over a vector by
declaring an iterator (`it`) that starts at the beginning
of the vector and increments until it reaches the end.

> [!IMPORTANT]
> The `end()` function returns an iterator pointing to the
> element following the last element of the vector, _not_ the
> last element itself. It is like the memory address one past
> the end of the vector and should not be dereferenced.

```cpp

```
