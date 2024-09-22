# C++ Study Sheet

Modern features of C++ are used when possible.

For example, we know how to write a for loop...

```cpp
for (int i = 0; i < 10; i++)
    cout << i << endl;
```

But consider the following:

```cpp
for (auto i : views::iota(0, 10))
    cout << i << endl;
```

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
for auto& x : v) x *= 2;
```

## User-Defined Types

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

### User-Defined Literals

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

### Remember

- Use 'class' to hide representation and provide an interface.
- Use 'struct' to group related data without hiding.
- Prefer 'enum class' over plain enums.
- Consider std::variant as a type-safe alternative to unions.
- Use user-defined literals for expressive value specification.

## Modularity

### Separate Compilation

C++ supports separate compilation.
You can define interfaces in header files and implementations in source files:

```cpp
// DNA.h
class DNA {
public:
    DNA(std::string seq);
    void addNucleotide(char n);
    size_t length() const;
private:
    std::string sequence;
};

// DNA.cpp
#include "DNA.h"

DNA::DNA(std::string seq) : sequence(std::move(seq)) {}

void DNA::addNucleotide(char n) {
    sequence += n;
}

size_t DNA::length() const {
    return sequence.length();
}
```

- namespaces
- function arguments and return values

## Error Handling

- exceptions
- invariants
- error-handling alternatives
- assertions

## Classes

- concrete types
- abstract types
- virtual functions
- class hierarchies

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

- `vector`
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
