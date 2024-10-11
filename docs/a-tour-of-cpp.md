---
render_macros: true
---

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

{{ source_code('src/basics.cpp') }}

### Accessing elements in a vector within a loop

| Syntax                               | Description                                  |
| ------------------------------------ | -------------------------------------------- |
| `for (auto element : vector)`        | Creates a copy of each element in the vector |
| `for (auto &element : vector)`       | Allows you to modify the elements            |
| `for (const auto &element : vector)` | Efficient way to iterate over a vector       |

> [!NOTE]
> The `&` in a variable declaration means that the variable is a reference to
> the object, not a copy of the object itself. The `const` qualifier ensures
> that the elements are not modified.

### Using iterators to access elements in a vector

```cpp
for (auto it = vector.begin(); it != vector.end(); it++) {
    cout << *it << endl;  // Dereference the iterator to get the value
}
```

The `end()` function returns an iterator pointing to the element
following the last element of the vector, _not_ the last element
itself. It is like the memory address one past the end of the
vector and should not be dereferenced.

Jump ahead to [Iterators](#iterators) for more information.

### Character conversion

```cpp
char ch = 'a';      // the ASCII value of 'a' is 97
int i = ch;         // i becomes 97

char c = '1';       // the ASCII value of '1' is 49
int i = c - '0';    // i becomes 1

int j = 1;          // what does the char value 1 look like?
char c = j + '0';   // c becomes '1'
```

> [!TIP]
> You can always check `man ascii` to view the ASCII table.

## User-Defined Types

- Use `class` to hide representation and provide an interface.
- Use `struct` to group related data without hiding.
- Prefer `enum class` over plain enums.
- Consider `std::variant` as a type-safe alternative to unions.
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

Nucleotide base = Nucleotide::A;
```

### `union`

Modern C++ prefers `std::variant` over unions.

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

Use 'using' for type aliases: `using DNAStrand = std::vector<Nucleotide>;`

I don't like using these in C because they obscure the type of the variable.

## Modularity

Declarations (interfaces, .h, .hpp) and definitions (implementations, .c, .cpp)
should be separate. Where modules are supported (C++20), use them!

> [!TIP]
> Header files should emphasize logical structure.

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

- Faster compilation (parsed once, not per translation unit)
- No need for include guards
- Better control over what's exported
- Fewer macro-related issues

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

#### Make Your Own `module std`

If an implementation does not currently support modules or lacks a standard
module equivalent, we can revert to using traditional headers, which are
widely available and standardized.
The challenge lies in identifying the necessary headers to include.

> [!CAUTION]
> Modules deliberately don’t export macros.
> If you need macros, use `#include` instead.

##### `std.h` Header

We can cram all the headers we want into a single header file, `std.h`, then include
it in our source files, but `#include`ing so much can give very slow compiles [Stroustrup,2021b].

##### `std` "Module"

It includes all necessary headers in the global module fragment (before
`export module std;`), then exports specific entities from the standard library.

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

##### Import a header unit

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

##### Actually defining the module

File: `std.cppm` (or `std.ixx`)

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

### Virtual Functions

A virtual function is a member function that can be overridden in a derived class.
They are used to achieve polymorphism, where a pointer or reference to a base
class can refer to objects of its derived classes.

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

A lambda function is an anonymous function that can capture variables from its
surrounding scope. It is defined using the following syntax:

```cpp
// template
[capture](parameters) -> return_type {
    // function body
}

// example
[](const auto& a, const auto& b) {
    return a.second < b.second;
}
```

Here, the lambda function takes two arguments `a` and `b` and returns `true` if
the `second` member of `a` is less than the `second` member of `b`.

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

```cpp
template<typename Iter, typename T>
Iter find(Iter first, Iter last, const T& value) {
    while (first != last && *first != value) ++first;
    return first;
}

std::vector<int> v = {1, 2, 3, 4, 5};
auto it = find(v.begin(), v.end(), 3);
```

### Variadic Templates

Variadic templates allow functions and classes to accept
any number of arguments of any type.

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

Templates are compiled when instantiated, which happens in the translation unit
where they are used, requiring template definitions to be available in headers.

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

> [!WARNING]
> You cannot define a template in a .cpp file and then use it in another .cpp
> file. The definition must be available at the point of instantiation.
> A workaround is to explicitly instantiate the template for the types you need.

## Standard Library

Provides the most common fundamental data structures together with
the fundamental algorithms used on them.

## Strings and Regular Expressions

C++ has its own string type, `std::string`, which is a part of the standard
library and is not the same as a `char*` we see in C.

### Strings

#### Initialization and Basic Operations

```cpp
string s = "hello";
size_t len = s.length();
char first = s[0];
s += " world";  // concatenation, s = "hello world"

// get a substring
string sub = s.substr(1, 5);  // sub = "ello"
```

#### Conversions

```cpp
// use functions from <string>
int num = stoi("123");
string str = to_string(123);
```

> [!TIP]
> These functions throw exceptions if the conversion fails.

#### Splitting strings

Use `std: istringstream` to split a whitespace-separated string into tokens:

```cpp
string s = "Hello, world!";
istringstream iss(s);
string token;
while (iss >> token) {
    cout << token << endl;
}
```

Use `std::getline()` to split a string by another delimiter:

```cpp
string time = "12:34:56";
int seconds = 10;
stringstream ss(time);
string item;
vector<int> time_parts;

while (getline(ss, item, ':')) {
    time_parts.push_back(stoi(item));
}
```

#### More string manipulations

##### Formatting output

Use an output string stream to concatenate strings.

```cpp
ostringstream oss;
os << setfill('0') << setw(2) << hours << ":" << setw(2) <<
minutes << ":" << setw(2) << seconds;
string result = os.str();
```

> [!NOTE]
> The `setfill()` and `setw()` manipulators from the `<iomanip>`
> header are used to set the fill character and the width of the output field.

##### Trimming whitespace

Use the `std::string::find_first_not_of()` and
`std::string::find_last_not_of()` functions to trim leading/trailing whitespace.

```cpp
// Trim any leading or trailing spaces
t1.erase(0, t1.find_first_not_of(' '));
t1.erase(t1.find_last_not_of(' ') + 1);
```

##### Find and Replace

```cpp
std::string replace_substring(const std::string& text, const std::string& old, const std::string& newSubstr) {
    string result = text;
    size_t pos = 0;

    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), newSubstr);
        pos += newSubstr.length(); // Move past the new substring
    }
    return result;
}
```

##### Reverse a string

```cpp
// reverse a string in place using two pointers
for (auto i = 0; i < s.size() / 2; i++) {
    swap(s[i], s[n - i - 1]);
}

// or use the reverse function
reverse(s.begin(), s.end());

// or use the reverse iterator with the constructor
string reversed(s.rbegin(), s.rend());
```

### `std::string_view`

### Regular Expressions in C++

## Input and Output

- state
- user-defined types
- formatting
- streams
- c-style
- file system

## Containers

### Vectors

```cpp
// reverse a vector
reverse(vec.begin(), vec.end());

// copy with simple assignment
vector<int> vec_copy = vec;

// append a vector to another vector
vec1.insert(vec1.end(), vec2.begin(), vec2.end());

// sort a vector
sort(vec.begin(), vec.end());

// sort a vector of pairs by the first element
sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
});

// Custom comparator
sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });

// binary search
bool found = binary_search(vec.begin(), vec.end(), target);
auto it = lower_bound(vec.begin(), vec.end(), target);
```

#### find

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

### Maps and Sets

```
unordered_map<int, int> map;
map[key] = value;
if (map.count(key)) { /* key exists */ }

unordered_set<int> set;
set.insert(value);
if (set.count(value)) { /* value exists */ }
```

### Queue

```
queue<int> q;
q.push(1);
int front = q.front();
q.pop();
```

### Stack

```
stack<int> s;
s.push(1);
int top = s.top();
s.pop();
```

### Priority Queue (Heap)

```
// Max heap
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

maxHeap.push(1);
int top = maxHeap.top();
maxHeap.pop();
```

- `list`
- `forward_list`
- `map`
- `unordered_map`
- allocators

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
- `std::transform`: Applies a function to each element in a range and stores the
  result in another range.
- `std::accumulate`: Computes the sum of a range of elements.

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

#### `std::sort`

```cpp
std::sort(RandomAccessIterator first, RandomAccessIterator last);
```

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

In practice:

```cpp
if (library_catalog.find(book_id) != library_catalog.end()) {
    std::cout << "Book found!" << '\n';
} else {
    std::cout << "Book not found!" << '\n';
}
```

#### `std::transform`

```cpp
std::transform(InputIterator1 first1, InputIterator1 last1, InputIterator2
first2, OutputIterator result, BinaryOperation op);
```

#### `std::accumulate`

The STL also provides `std::multplies` for multiplication and `std::divides` for
division.

```cpp
#include <iostream>
#include <vector>
#include <numeric>  // For std::accumulate

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    int sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "Sum: " << sum << '\n';  // Sum: 15

    int product = std::accumulate(data.begin(), data.end(), 1,
            std::multiplies<int>());
    std::cout << "Product: " << product << '\n';  // Product: 120

    // Using std::accumulate with a lambda expression
    int sum_of_squares = std::accumulate(data.begin(), data.end(), 0, [](int sum, int val) {
            return sum + val * val;
            });
    std::cout << "Sum of Squares: " << sum_of_squares << '\n';  // Sum of Squares: 55

    std::vector<int> data2 = {6, 7, 8, 9, 10};

    // Combining two vectors element-wise and accumulating the result
    int combined_sum = std::accumulate(data.begin(), data.end(), 0, [&data2, i = 0](int sum, int val) mutable {
            return sum + val + data2[i++];
            });
    std::cout << "Combined Sum: " << combined_sum << '\n';  // Combined Sum: 55

    // append data2 to data
    data.insert(data.end(), data2.begin(), data2.end());

    // Use std::accumulate with a lambda expression to sum even numbers
    int sum_of_evens = std::accumulate(data.begin(), data.end(), 0, [](int sum, int val) {
        return sum + ((val % 2 == 0) ? val : 0);
    });

    int weighted_sum = std::accumulate(data.begin(), data.end(), 0, [&weights, i = 0](int sum, int val) mutable {
            return sum + val * weights[i++];
            });

    return 0;
}
```

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
