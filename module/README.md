# Make Your Own `module `std`

If an implementation does not currently support modules or lacks a standard module equivalent,
we can revert to using traditional headers, which are widely available and standardized.
The challenge lies in identifying the necessary headers to include.

> [!CAUTION]
> Modules deliberately don’t export macros.
> If you need macros, use `#include` instead.

## `std.h` Header

We can cram all the headers we want into a single header file, `std.h`, then include
it in our source files, but `#include`ing so much can give very slow compiles [Stroustrup,2021b].

## `std` "Module"

It includes all necessary headers in the global module fragment (before `export module std;`),
then exports specific entities from the standard library.

```cpp
module;
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <algorithms>
// ...

export module std;
export istream;
export ostream;
export iostream;
// ...
```

## Import a header unit

```cpp
export module std;

export import "iostream";
export import "string";
export import "vector";
export import "list";
export import "memory";
export import "algorithms";
// ...
```

> [!WARNING]
> This approach has several drawbacks:
>
> - It treats each header as a separate module-like entity.
> - It can inject names into the global namespace.
> - It may leak macros, which regular modules don't do.
>   But it's still pretty cool.

## Actually defining the module

File: `std.cppm`

```cpp
export module std;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

export using std::cout;
export using std::cin;
export using std::string;
export using std::vector;
```

Command:

```sh
clang++ -std=c++20 -fmodules-ts -c std.cppm
```

Error:

```console
std.cppm:8:19: error: using declaration referring to 'cout' with module linkage cannot be exported
```

It looks like we can't export `using` declarations on Apple clang version 15.0.0 (clang-1500.3.9.4)
