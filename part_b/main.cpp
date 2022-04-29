#include <iostream>

#define NAME(x) #x

void B1() {
    std::cout << "(B)(1) Deleting the same memory twice" << std::endl << std::endl;

    std::string *a = new std::string{"Bob"};
    std::cout << "Created an `std::string` using `new`; the pointer is captured to a variable `a`" << std::endl;
    std::cout << "Dereferencing `a` yields: " << *a << std::endl;

    std::string *b = a;
    std::cout << "Created another pointer `b` to have the same value as `a`" << std::endl;
    std::cout << "Both pointers `a` and `b` points to " << a << std::endl;

    std::cout << "Applying `delete` to `a` will return the string's memory to the free-store" << std::endl;
    delete a;

    std::cout << "Since `delete` removes the object and not the pointer, printing `a` and `b` shows "
                 "that they still point to the same location:" << std::endl;
    std::cout << "a: " << a << "  |  b: " << b << std::endl;

    std::cout << "This means that `a` and `b` are now dangling because they both point to deallocated memory"
              << std::endl;
    std::cout << "Attempting to apply `delete` on to `b` will result in an error, for example:" << std::endl;

    // delete b;

    // In Clang,
    std::cerr << "part_b(36739," << a << ") malloc: *** error for object " << a
              << ": pointer being freed was not allocated" << std::endl;
    std::cerr << "part_b(36739," << a << ") malloc: *** set a breakpoint in malloc_error_break to debug" << std::endl;
}

int main() {
    B1();
}