# C++ sandbox

A collection of C++ code snippets and examples.

Check out the [website](https://rdnajac.tech/cpp-sandbox/) for more information.

## Build with [CMake](https://cmake.org/)

```sh
mkdir build && cd build && cmake .. && make -j$(nproc)
```

## Test with [Catch2](https://github.com/catchorg/Catch2)

```sh
./build/test/test
```

## Documentation with [MkDocs](https://www.mkdocs.org/)

```sh
pip install -r requirements.txt
mkdocs serve
# open localhost:8000
```

## Resources

There are some cool guides included them as a submodules in this repo so
they can be easily accessed and updated. The search plugin that comes with
Material for MkDocs theme can be used to search through all the resources,
even if they're excluded from the navbar.

- [C++ Reference](https://en.cppreference.com/w/)
- [GeeksforGeeks](https://www.geeksforgeeks.org/)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)
