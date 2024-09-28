#include <iostream>
#include <memory>

// Function declaration
void classify_pointer(const void *p);

int g = 0;
int *h = &g;

void cp(int **a) {
    int *x = *a;
    a = &x;

    classify_pointer(x);        // (4.1.2) NEITHER: x points to g
    classify_pointer(&a);       // (4.1.3) STACK: a is a local variable
    classify_pointer(a);        // (4.1.4) STACK: a points to x

    // Use std::unique_ptr for automatic memory management
    std::unique_ptr<int[]> heap_array = std::make_unique<int[]>(100);
    *a = heap_array.get();

    classify_pointer(a);        // (4.1.5) STACK: a still points to x
    classify_pointer(++*a);     // (4.1.6) HEAP: x points to heap

    h = x;

    // heap_array will be automatically freed when it goes out of scope
}

int main() {
    cp(&h);

    // (4.1.7) No need to manually free memory due to use of std::unique_ptr

    return 0;
}
