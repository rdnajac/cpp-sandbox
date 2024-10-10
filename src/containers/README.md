# STL Containers

- [Vector](#vector)
- [List](#list)
- [Deque](#deque)
- [Stack](#stack)
- [Queue](#queue)
- [Priority Queue](#priority-queue)
- [Set](#set)
- [Map](#map)
- [Unordered Map](#unordered-map)

## Check if a key is in an `unordered_map`

```cpp
// Using find() to access a book's title
auto it = library_catalog.find("book1");
if (it != library_catalog.end())
    std::cout << it->second << std::endl; // Output: "A Tale of Two Cities"
else
    std::cout << "Key not found" << std::endl;

// Using find() to access a nonexistent key
auto it_nonexistent = library_catalog.find("book100");
if (it_nonexistent != library_catalog.end())
    std::cout << it_nonexistent->second << std::endl;
else
    std::cout << "Key not found" << std::endl; // Output: "Key not found"
```
