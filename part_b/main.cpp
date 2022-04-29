#include <iostream>
#include <memory>
#include <utility>

#define NAME(x) #x

void B1() {

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
    std::cout << "part_b(36739," << a << ") malloc: *** error for object " << a
              << ": pointer being freed was not allocated" << std::endl;
    std::cout << "part_b(36739," << a << ") malloc: *** set a breakpoint in malloc_error_break to debug" << std::endl;

}

void B2() {

    class Student {
     public:
        explicit Student(std::string name) : name(std::move(name)) {};
        ~Student() { std::cout << "Destroyed " << name << std::endl; }
        std::string GetName() { return name; }
     private:
        std::string name;
    };

    {
        std::cout << "Entering a block" << std::endl;
        std::cout << "{" << std::endl;

        std::cout << "  Creating a `Student` instance named Bob using `unique_ptr` in the block" << std::endl;
        std::unique_ptr<Student> s{std::make_unique<Student>("Bob")};

        std::cout << "  Inside the block, we can access the instance using the unique pointer" << std::endl;
        std::cout << "  For example: this student's name is " << s->GetName() << std::endl;
        std::cout << "  Once we leave this scope, the smart pointer ensures that the object is destroyed" << std::endl;

        std::cout << "}" << std::endl;
        std::cout << "Leaving this block" << std::endl;
    }

}

int main() {
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(1) Deleting the same memory twice" << std::endl << std::endl;
    B1();
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(2) Using smart pointers to deal with `new` instance" << std::endl << std::endl;
    B2();
}