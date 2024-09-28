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
9. [Standard-Library](#library-overview)
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

## User-Defined Types

- Use 'class' to hide representation and provide an interface.
- Use 'struct' to group related data without hiding.
- Prefer 'enum class' over plain enums.
- Consider std::variant as a type-safe alternative to unions.
- Use user-defined literals for expressive value specification.

### Structures

Structures group related data elements:

```cpp
struct DNASequence {
    std::vector<Nucleotide> nucleotides;
    std::string source;
};
```

### Classes

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

### Enumerations

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

### Unions

Modern C++ prefers std::variant over unions:

```cpp
#include <variant>

std::variant<DNA, std::string> genetic_info;
genetic_info = DNA({Nucleotide::A, Nucleotide::T});
genetic_info = "ATGC";  // Now contains a string
```

### User-Defined Literals:/

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

Use 'using' for type aliases:

using DNAStrand = std::vector<Nucleotide>;

> [!NOTE]
> I don't like using these in C because they obscure the type of the variable.
> However, I don't have enough experience with C++ to know if if this is best
> practice.

## Modularity

Declarations (interfaces, .h, .hpp) and definitions (implementations, .c, .cpp)
should be separate. Where modules are supported (C++20), use them!

> [!TIP]
> Header files should emphasize logical structure.

### namespaces

### modules

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

### Heirarchies

## Essential Operations

- copy and move
- resource management
- operator overloading
- conventional operations
- user-defined literals

## Templates

- parameterized types
- parameterized operations
- template mechanisms

## Concepts and Generic Programming

- concepts
- generic programming
- variadic templates
- template compilation model

## Standard-Library

- components
- organization

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

- iterators
- use of predicates
- algorithm overview
- parallel algorithms

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
