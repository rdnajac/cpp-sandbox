# A Tour of C++

During my time at Columbia University, I had the privilege of taking
[Bjarne Stroustrup's](https://www.stroustrup.com/) course, "Design using C++".
Now that I have graduated, I've decided to compile all of my notes into a
comprehensive guide. This document serves as an easy reference to accompany the
repository of code snippets and examples I have been developing.

## Attribution

The material in this document is based on concepts and information from:
Stroustrup, B. (2022). A Tour of C++ (C++ In-Depth Series) (3rd ed.). Addison-Wesley Professional.

## Table of Contents

1. [The Basics](#the-basics)
2. [User-Defined Types](#user-defined-types)
3. [Modularity](#modularity)
4. [Error Handling](#error-handling)
5. [Classes](#classes)
6. [Essential Operations](#essential-operations)
7. [Templates](#templates)
8. [Concepts and Generic Programming](#concepts-and-generic-programming)
9. [Standard-Library](#standard-library)
10. [Strings and Regular Expressions](#strings-and-regular-expressions)
11. [Input and Output](#input-and-output)
12. [Containers](#containers)
13. [Algorithms](#algorithms)
14. [Ranges](#ranges)
15. [Pointers and Containers](#pointers-and-containers)
16. [Utilities](#utilities)
17. [Numerics](#numerics)
18. [Concurrency](#concurrency)

## The Basics

```cpp
using namespace std;    // make names from std visible without std::
```

### Variables

Use `auto` to let the compiler deduce the type of a variable
unless there is a specific reason to specify the type.

```cpp
auto i = 7;     // i is an int
auto d = 1.2;   // d is a double
auto qq {true}; // qq is a bool
```

### Constants

Use `const` to define a constant. Use `constexpr` for a constant expression.
For example:

```cpp
constexpr double square(double x) { return x*x; }
```

### Loops

A "range-`for`-statement" traverses a sequence in the simplest way:

```cpp
int v[] = {0, 1, 2, 3, 4, 5};

for (auto x : v) cout << x << '\n';
```

Another example:

```cpp
for (auto& x : v) x *= 2;
```

#### Accessing elements in a vector

##### `for (const auto &element : vector)`

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

##### `for (auto element : vector)`

This creates a copy of each element in the vector. If the
elements are large, this can be inefficient. Use a reference
(`&`) instead to avoid copying.

##### `for (auto &element : vector)`

This allows you to modify the elements of the vector.

```cpp
vector<int> some_vector = {1, 2, 3, 4, 5};
for (auto &element : some_vector) {
    element *= 2;
}
cout << "Doubled vector: "; // 2 4 6 8 10
```

##### `for (auto it = vector.begin(); it != vector.end(); it++)`

This is the traditional way to iterate over a vector by
declaring an iterator (`it`) that starts at the beginning
of the vector and increments until it reaches the end.

> [!IMPORTANT]
> The `end()` function returns an iterator pointing to the
> element following the last element of the vector, _not_ the
> last element itself. It is like the memory address one past
> the end of the vector and should not be dereferenced.

## User-Defined Types

- Use 'class' to hide representation and provide an interface.
- Use 'struct' to group related data without hiding.
- Prefer 'enum class' over plain enums.
- Consider std::variant as a type-safe alternative to unions.
- Use user-defined literals for expressive value specification.

### `struct`

Structures group related data elements:

```cpp
struct DNASequence {
    std::vector<Nucleotide> nucleotides;
    std::string source;
};
```

### `class`

Classes extend structures by adding member functions:

```cpp
class DNA {
public:
    DNA(std::vector<Nucleotide> seq) : sequence{std::move(seq)} {}
    void addNucleotide(Nucleotide n) { sequence.push_back(n); }
    size_t length() const { return sequence.size(); }
private:
    std::vector<Nucleotide> sequence;
};
```

Usage:

```cpp
DNA dna({Nucleotide::A, Nucleotide::T, Nucleotide::G});
dna.addNucleotide(Nucleotide::C);
std::cout << "DNA length: " << dna.length() << '\n';
```

Jump ahead to [Classes](#classes) for more information.

### `enum`

Use strongly typed enumerations:

```cpp
enum class Nucleotide {
    A, // Adenine
    T, // Thymine
    G, // Guanine
    C  // Cytosine
};
```

Nucleotide base = Nucleotide::A;

### `union`

Modern C++ prefers std::variant over unions:

```cpp
#include <variant>

std::variant<DNA, std::string> genetic_info;
genetic_info = DNA({Nucleotide::A, Nucleotide::T});
genetic_info = "ATGC";  // Now contains a string
```

### User-Defined Literals:

Define custom literals:

```cpp
DNA operator""_dna(const char* seq, size_t len)
{
    std::vector<Nucleotide> nucleotides;
    for (size_t i = 0; i < len; ++i) {
        switch(seq[i]) {
            case 'A': nucleotides.push_back(Nucleotide::A); break;
            case 'T': nucleotides.push_back(Nucleotide::T); break;
            case 'G': nucleotides.push_back(Nucleotide::G); break;
            case 'C': nucleotides.push_back(Nucleotide::C); break;
            default: throw std::invalid_argument("Invalid nucleotide");
        }
    }
    return DNA(nucleotides);
}

auto my_dna = "ATGC"_dna;
```

### Type Aliases

Use 'using' for type aliases: `using DNAStrand = std::vector<Nucleotide>;`

> [!NOTE]
> I don't like using these in C because they obscure the type of the variable.

## Modularity

Declarations (interfaces, .h, .hpp) and definitions (implementations, .c, .cpp)
should be separate. Where modules are supported (C++20), use them!

> [!TIP]
> Header files should emphasize logical structure.

### Make Your Own `module `std`

If an implementation does not currently support modules or lacks a standard module equivalent,
we can revert to using traditional headers, which are widely available and standardized.
The challenge lies in identifying the necessary headers to include.

> [!CAUTION]
> Modules deliberately don’t export macros.
> If you need macros, use `#include` instead.

#### `std.h` Header

We can cram all the headers we want into a single header file, `std.h`, then include
it in our source files, but `#include`ing so much can give very slow compiles [Stroustrup,2021b].

#### `std` "Module"

It includes all necessary headers in the global module fragment (before `export module std;`),
then exports specific entities from the standard library.

```cpp
module;
#include <iostream>
#include <string>
#include <vector>
// ...

export module std;
export iostream;
export string;
export vector;
// ...
```

#### Import a header unit

```cpp
export module std;

export import "iostream";
export import "string";
export import "vector";
// ...
```

> [!WARNING]
> This approach has several drawbacks:
>
> - It treats each header as a separate module-like entity.
> - It can inject names into the global namespace.
> - It may leak macros, which regular modules don't do.
>
>   But it's still pretty cool.

#### Actually defining the module

File: `std.cppm` (or std.ixx)

Command:

```sh
clang++ -std=c++20 -fmodules-ts -c std.cppm
```

Error:

```console
std.cppm:8:19: error: using declaration referring to 'cout' with module linkage cannot be exported
```

> [!WARNING]
> It looks like we can't export `using` declarations on Apple clang version 15.0.0 (clang-1500.3.9.4)

### Namespaces

Namespaces help prevent name collisions and organize code:

```cpp
namespace genetics {
    class DNA { /* ... */ };
    class RNA { /* ... */ };
}

// Use with qualification
genetics::DNA myDNA;

// Or bring specific names into scope
using genetics::RNA;
RNA myRNA;

// Avoid bringing entire namespaces into global scope
// using namespace genetics; // Not recommended
```

Use namespaces to group related functionality and avoid polluting the global namespace.

### Modules

Modules (C++20) offer better encapsulation and faster compilation than header files:

```cpp
// genetics.ixx
export module genetics;

export class DNA { /* ... */ };
export class RNA { /* ... */ };

// Not exported, internal to module
class Ribosome { /* ... */ };
```

Usage:

```cpp
import genetics;
genetics::DNA myDNA;
```

Benefits:

- Faster compilation (parsed once, not per translation unit)
- No need for include guards
- Better control over what's exported
- Fewer macro-related issues

## Error Handling

### Exceptions

You can throw custon exceptions after defining a class derived from
std::exception. For example:

```cpp
class BadLengthException : public std::exception {
private:
    int length;
    std::string message;

public:
    BadLengthException(int len) : length(len) {
        message = std::to_string(length);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};
```

- invariants
- error-handling alternatives
- assertions

## Classes

Three important kinds of C++ classes are:

- concrete types
- abstract types
- virtual functions

### Concrete Types

> They behave "just like built-in types."!

#### Classical user-defined arithmetic type

```cpp
class complex {
    double re, im; // representation: two doubles
public:
    complex(double r, double i) :re{r}, im{i} {}    // construct complex from two scalars
    complex(double r) :re{r}, im{0} {}              // construct complex from one scalar
    complex() :re{0}, im{0} {}                      // default complex: {0,0}
    complex(complex z) :re{z.re}, im{z.im} {}       // copy constructor

    double real() const { return re; }
    void real(double d) { re=d; }
    double imag() const { return im; }
    void imag(double d) { im=d; }

    complex& operator+=(complex z)
    {
        re+=z.re;       // add to re and im
        im+=z.im;
        return *this;   // return the result
    }

    complex& operator-=(complex z)
    {
        re-=z.re;
        im-=z.im;
        return *this;
    }

    complex& operator*=(complex); // defined out-of-class somewhere
    complex& operator/=(complex); // defined out-of-class somewhere
};
```

### Abstract Types

Insulates the user from implementation details by decoupling the interface from
the representation.

> Since we don’t know anything about the representation of an
> abstract type (not even its size), we must allocate objects on the free store
> and access them through references or pointers.

```cpp
class Container {
public:
    virtual double& operator[](int) = 0;    // pure virtual function
    virtual int size() const = 0;           // const member function
    virtual  ̃Container() {}                 // destructor

    // const member function  // destructor (§5.2.2)
};
```

> [!NOTE]
> The curious `=0` syntax says the function is pure virtual;
> that is, some class derived from Container must define the function.

### Heirarchies

Syntax:

```cpp
class Vector_container : public Container {
    std::vector<double> v;
    public:
    double& operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
};
```

> [!NOTE]
> We use override to indicate that we are overriding a virtual function.

## Essential Operations

### Copy and Move

```cpp
class Vector {
public:
    Vector(const Vector& a);              // copy constructor
    Vector& operator=(const Vector& a);   // copy assignment

    Vector(Vector&& a);                   // move constructor
    Vector& operator=(Vector&& a);        // move assignment
};

Vector::Vector(const Vector& a)           // copy constructor
    :elem{new double[a.sz]},              // allocate space for elements
     sz{a.sz}
{
    for (int i=0; i!=sz; ++i)             // copy elements
        elem[i] = a.elem[i];
}

Vector::Vector(Vector&& a)                // move constructor
    :elem{a.elem},                        // "grab the elements" from a
     sz{a.sz}
{
    a.elem = nullptr;                     // now a has no elements
    a.sz = 0;
}
```

### Resource Management

```cpp
template<typename T>
class Vector {
private:
    T* elem;   // elem points to an array of sz elements of type T
    int sz;
public:
    Vector(int s) :elem{new T[s]}, sz{s}  // constructor: acquire resources
    {
        for (int i=0; i!=s; ++i)          // initialize elements
            elem[i] = T{};
    }
    ~Vector() { delete[] elem; }          // destructor: release resources
    // ... copy and move operations ...
};
```

### Operator Overloading

```cpp
complex& complex::operator+=(complex z)
{
    re+=z.re;    // add to the real part
    im+=z.im;    // add to the imaginary part
    return *this;
}

complex operator+(complex a, complex b)
{
    return a+=b;
}
// and so on...
```

### Conventional Operations

```cpp
class Vector {
public:
    T& operator[](int i) { return elem[i]; }              // for non-const Vectors
    const T& operator[](int i) const { return elem[i]; }  // for const Vectors
    int size() const { return sz; }
};

bool operator==(const Vector& a, const Vector& b)
{
    if (a.size() != b.size()) return false;
    for (int i=0; i!=a.size(); ++i)
        if (a[i]!=b[i]) return false;
    return true;
}

bool operator!=(const Vector& a, const Vector& b)
{
    return !(a==b);
}
```

### User-Defined Literals

```cpp
constexpr complex<double> operator""i(long double d)
{
    return {0,d};  // complex is a literal type
}
```

## Templates

`<T>`

### Parameterized Types

```cpp
template<typename T>
class Vector {
private:
    T* elem;   // elem points to an array of sz elements of type T
    int sz;
public:
    explicit Vector(int s);
    ~Vector() { delete[] elem; }

    // ... copy and move operations ...

    T& operator[](int i);
    const T& operator[](int i) const;
    int size() const { return sz; }
};

Vector<char> vc(200);          // vector of 200 characters
Vector<string> vs(17);         // vector of 17 strings
Vector<list<int>> vli(45);     // vector of 45 lists of integers
```

### Parameterized Operations

```cpp
template<typename Container, typename Value>
Value sum(const Container& c, Value v)
{
    for (auto x : c)
        v += x;
    return v;
}

void user(Vector<int>& vi, std::list<double>& ld, std::vector<complex<double>>& vc)
{
    int x = sum(vi,0);              // the sum of a vector of ints (add ints)
    double d = sum(vi,0.0);         // the sum of a vector of ints (add doubles)
    double dd = sum(ld,0.0);        // the sum of a list of doubles
    auto z = sum(vc,complex{0.0});  // the sum of a vector of complex<double>
}
```

### Template Mechanisms

```cpp
// Variable templates
template<typename T>
constexpr T pi = T{3.1415926535897932385};  // variable template

// Template aliases
template<typename Value>
using String_map = Map<string,Value>;  // Map is some map template

String_map<int> m;  // m is a Map<string,int>

// Variadic templates
template<typename T, typename... Tail>
void print(T head, Tail... tail)
{
    cout << head << ' ';
    if constexpr(sizeof...(tail) > 0)
        print(tail...);
}

print(42, "hello", 3.14, "world");

// Fold expressions
template<typename... T>
int sum(T... v)
{
    return (v + ... + 0);  // add all elements of v starting with 0
}

int x = sum(1, 2, 3, 4, 5);  // x becomes 15
```

#### Lambda Functions

```cpp
[capture](parameters) -> return_type {
    // function body
}
```

| Capture Mode | Description                                             |
| ------------ | ------------------------------------------------------- |
| `[]`         | No capture                                              |
| `[x]`        | Capture `x` by value                                    |
| `[&x]`       | Capture `x` by reference                                |
| `[=]`        | Capture all variables by value                          |
| `[&]`        | Capture all variables by reference                      |
| `[=, &x]`    | Capture all variables by value, except `x` by reference |
| `[&, x]`     | Capture all variables by reference, except `x` by value |

## Concepts and Generic Programming

### Concepts

###

Concepts define requirements on template arguments,
enabling better error messages and overload resolution.

```cpp
template<typename T>
concept Arithmetic = requires(T x, T y) {
    { x + y } -> std::convertible_to<T>;
    { x - y } -> std::convertible_to<T>;
    { x * y } -> std::convertible_to<T>;
    { x / y } -> std::convertible_to<T>;
};

template<Arithmetic T>
T sum(std::vector<T> const& v) {
    T result = 0;
    for (auto const& z : v) result += z;
    return result;
}
```

### Generic Programming

Generic programming allows writing algorithms that
work with any type satisfying certain requirements.

```
template<typename Iter, typename T>
Iter find(Iter first, Iter last, const T& value) {
    while (first != last && *first != value) ++first;
    return first;
}

std::vector<int> v = {1, 2, 3, 4, 5};
auto it = find(v.begin(), v.end(), 3);
```

### Variadic Templates

Variadic templates allow functions and classes to accept any number of arguments of any type.

```cpp
template<typename T>
void print(T arg) {
    std::cout << arg << '\n';
}

template<typename T, typename... Args>
void print(T first, Args... rest) {
    std::cout << first << ' ';
    print(rest...);
}

print(1, "hello", 3.14);
```

### Template Compilation Model

Templates are compiled when instantiated, which happens in the translation unit where they are used. This requires template definitions to be available in headers.

```cpp
// mylibrary.h
template<typename T>
T square(T x) { return x * x; }

// main.cpp
#include "mylibrary.h"
int main() {
    auto result = square(5);
}
```

## Standard-Library

Provides the most common fundamental data structures together with
the fundamental algorithms used on them.

## Strings and Regular Expressions

- strings
- string views
- regular expressions

## Input and Output

- state
- user-defined types
- formatting
- streams
- c-style
- file system

## Containers

### vector

#### insert

Insert expects an iterator and a value to insert:

```cpp
v.insert(v.begin() + 2, 5); // insert 5 at position 2
```

Use `v.begin()` to get an iterator to the beginning of the vector,
then add an offset to get the desired position.

#### append to end

Use `push_back` to append to the end of a vector:

```cpp
v.push_back(7);
```

### find

```cpp
void find_example() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  // parameters:
  // 1. begin iterator
  // 2. end iterator
  // 3. value to find
  auto it = std::find(v.begin(), v.end(), 3);
  if (it != v.end()) {
    std::cout << "Found: " << *it << std::endl;
  } else {
    std::cout << "Not found" << std::endl;
  }
}

```

#### find and insert after

Use `std::find` to find a value in a vector:

```cpp
auto it = std::find(v.begin(), v.end(), 5);
if (it != v.end()) {
    v.insert(it + 1, 6);
}
```

- `list`
- `forward_list`
- `map`
- `unordered_map`
- allocators
- container overview

## Algorithms

In addition to the containers themselves, the standard library provides a set of
algorithms that operate on them (like printing, searching, sorting, extracting,
subsets, etc.). These algorithms are designed to be efficient
and correct for all standard containers.

### Iterators

Iterators are objects that provide sequential access to container elements
without exposing the underlying structure. Essential for efficient manipulation
of data in C++ Standard Library containers.

1. Input Iterators: Read-only access.
2. Output Iterators: Write-only access.
3. Forward Iterators: Read and write, single-pass.
4. Bidirectional Iterators: Move both forward and backward.
5. Random-Access Iterators: Move to any element in constant time.

#### Using Iterators with std::vector

- Traversal: Use `begin()` to get an iterator to the first element and `end()` for the past-the-last element.
- Incrementing and Dereferencing:
  - `++it`: Move to the next element.
  - `*it`: Access the value at the current iterator position.

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    std::cout << *it << " "; // Output: 1 2 3 4 5
}
```

#### Modifying Elements with Iterators

Modify vector elements directly via iterators:

```cpp
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    *it *= 2; // Doubles each element
}
```

#### Reverse Iterators

Use `rbegin()` and `rend()` to traverse in reverse:

```cpp
for (auto rit = numbers.rbegin(); rit != numbers.rend(); ++rit) {
    std::cout << *rit << " "; // Output: 5 4 3 2 1
}
```

### STL Algorithms

STL algorithms are a collection of functions provided by the Standard
Template Library (STL) in C++. They perform common operations on sequences
of data, saving time and effort by leveraging well-tested and optimized
operations for tasks like searching, sorting, and transforming data.

Commonly used STL algorithms include:

- `std::for_each`: Applies a function to a range of elements.
- `std::sort`: Sorts a range of elements.
- `std::find`: Searches for a value in a range of elements.

#### `std::for_each`

```cpp
std::for_each(InputIterator first, InputIterator last, Function fn);
```

- `InputIterator first`: An iterator pointing to the start of the range.
- `InputIterator last`: An iterator pointing to one past the end of the range.
- `Function fn`: A function or function object (often a lambda) to apply to the elements in the range.

> [!IMPORTANT]
> Lambda functions are a concise way to define small functions inline.
> The syntax is `[] (parameters) { body }`.
> where the `[]` captures variables from the enclosing scope and parameters are
> passed to the lambda.

````cpp


#### `std::sort`

```cpp
std::sort(RandomAccessIterator first, RandomAccessIterator last);
````

- `RandomAccessIterator first`: An iterator pointing to the start of the range.
- `RandomAccessIterator last`: An iterator pointing to one past the end of the
  range.

#### `std::find`

```cpp
std::find(InputIterator first, InputIterator last, const T& value);
```

- `InputIterator first`: An iterator pointing to the start of the range.
- `InputIterator last`: An iterator pointing to one past the end of the range.
- `const T& value`: The value to search for in the range.

## Ranges

- views
- generators
- pipelines
- concepts overview

## Pointers and Containers

- pointers
- containers
- alternatives

## Utilities

- time
- function adaption
- type functions
- `source_location`
- `move()` and `forward()`
- bit manipulation

## Numerics

- mathematical functions
- numerical algorithms
- complex numbers
- random numbers
- vector arithmetic
- numeric limits
- mathematical constants

## Concurrency

- tasks and `thread`s
- sharing data
- waiting for events
- communicating tasks
- coroutines
