# C++ sandbox

A collection of C++ code snippets and examples.

## Building with CMake

This project uses CMake to build the examples. To build the project, run the
following commands:

```sh
mkdir build
cd build
cmake ..
make
```

### Testing

We use [Catch2](https://github.com/catchorg/Catch2) for testing. To run the
tests, run the following command:

```sh

```

## Projects

- TCP client/server
- `std::chrono`

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

I found this cool repo called
and I liked it so much, it's
built along with the rest of the docs.

### C++ Resources

[Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)

Access it [here](resources/modern-cpp-features/README.md).

When in doubt, check out the [C++ Reference](https://en.cppreference.com/w/).
