# C++ sandbox

A collection of C++ code snippets and examples.

## Build

[CMake](https://cmake.org/)

```sh
mkdir build
cd build
cmake ..
make
```

## Test

[Catch2](https://github.com/catchorg/Catch2)

## Projects

- TCP client/server

## `docs/`

Made with [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)

```sh
pip install -r requirements.txt
mkdocs serve
open http:localhost:8000
```

> [!NOTE]
> Each subdirectory in this repository contains a `README.md` file that is
> symlinked to the `docs/` directory so that the markdown is compiled into
> an HTML page that can be viewed in a browser with the rest of the docs.

## Resources

There are a lot of cool guides and resources out there and I've compiled
the ones I've found most helpful here and included them as a submodules
in this repo so that they can be easily accessed and updated. The search
plugin that comes with the Material for MkDocs theme can be used to search
through all the resources at once, even if they're excluded from the nav.

- [C++ Reference](https://en.cppreference.com/w/)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)
  - Access a copy of it [here](docs/resources/modern-cpp-features/README.md).
