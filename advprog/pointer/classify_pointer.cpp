#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <cstdint>

/** Given a pointer p, classify_pointer():
 *
 *      prints "STACK" if p contains an address on the stack;
 *      prints "HEAP" if p contains an address on the heap;
 *      prints "NEITHER" otherwise.
 */
void classify_pointer(const void *p) {
    // sbrk(0) returns the program break -- i.e., the top of the heap
    void *heap_top = sbrk(0);

    // ld adds the symbol _end for the end of all segments in ELF
    extern void *_end;
    void *heap_bottom = &_end;

    std::cout << std::setw(8) << std::left;

    if (reinterpret_cast<const void *>(&p) < p)
        std::cout << "STACK";
    else if (heap_bottom <= p && p < heap_top)
        std::cout << "HEAP";
    else
        std::cout << "NEITHER";

    std::cout << "\t" << p << "\t"
              << "(heap: " << heap_bottom << "<-->" << heap_top << ")" << std::endl;
}
