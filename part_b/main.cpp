#include <iostream>
#include <memory>
#include <utility>
#include <typeinfo>

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

// For (B)(2) and (B)(3)
class Student {
 public:
    explicit Student(std::string name) : name(std::move(name)) {};
    ~Student() { std::cout << "Destroyed " << name << std::endl; }
    std::string GetName() { return name; }
 private:
    std::string name;
};

void B2() {

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

void B3() {
    class ReportCard {
     public:
        explicit ReportCard(const std::string &name, const char &grade) :
            student(std::make_unique<Student>(name)),
            grade(std::make_unique<char>(grade)) {}
        ~ReportCard() {
            std::cout << "Destroying " << student->GetName() << "'s \"" << grade << "\" report card" << std::endl;
        }
     private:
     public:
        const std::unique_ptr<Student> &GetStudent() const { return student; }
        const std::unique_ptr<char> &GetGrade() const { return grade; }
        std::unique_ptr<Student> student{nullptr};
        std::unique_ptr<char> grade;
    };

    {
        std::cout << "Entering a block" << std::endl;
        std::cout << "{" << std::endl;

        std::cout << "  Creating a `ReportCard` instance for a `Student` named Alice using `unique_ptr`" << std::endl;
        std::cout << "  The `ReportCard` instance has a member that is a `unique_ptr` pointing to a `Student` instance"
                  << std::endl;
        std::unique_ptr<ReportCard> card{std::make_unique<ReportCard>("Alice", 'A')};

        std::cout << "  Once this `unique_ptr` goes out of scope, `~ReportCard()` will be automatically invoked"
                  << std::endl;
        std::cout << "  Because its members are also `unique_ptr`s, they too, will invoke their respective destructors"
                  << std::endl;

        std::cout << "  For visualization, a simple print statement is placed in `~ReportCard()` -- nothing \"special\""
                  << std::endl;

        std::cout << "}" << std::endl;
        std::cout << "Leaving this block" << std::endl;
    }
}

void B4() {

    std::cout << "A `unique_ptr` can be converted into a `shared_ptr` using the `std::move()`" << std::endl;
    std::unique_ptr<std::string> u{std::make_unique<std::string>("test")};
    std::cout << "Unique pointer `u` points to " << u << std::endl << std::endl;

    std::cout << "Using `std::move()` on `u`, we can convert `u` into a shared pointer" << std::endl;
    std::shared_ptr<std::string> s = std::move(u);
    std::cout << "Shared pointer `s` points to " << s << std::endl;
    std::cout << "And the old unique pointer `u` points to " << u << std::endl;

}

void B5() {

    std::cout << "Creating a `shared_ptr` called `name`" << std::endl;
    std::shared_ptr<std::string> name{std::make_shared<std::string>("Bob")};
    std::cout << "`name` points to " << name << std::endl << std::endl;

    std::cout << "Creating a `weak_ptr` to called `weak_name` to observe `name`" << std::endl;
    std::weak_ptr<std::string> weak_name{name};

    std::cout << "Using `expired()`, we can check whether the ownership is still valid" << std::endl
              << "weak_name.expired(): " << weak_name.expired() << std::endl << std::endl;

    std::cout << "Invoking `reset()` on the shared_ptr `name`" << std::endl;
    name.reset();
    std::cout << "`name` now points to " << name << std::endl;

    std::cout << "With the weak_ptr, we can check whether the object is still alive" << std::endl
              << "weak_name.expired(): " << weak_name.expired() << std::endl << std::endl;

}

int main() {
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(1) Deleting the same memory twice" << std::endl << std::endl;
    B1();
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(2) Using smart pointers to deal with `new` instance" << std::endl << std::endl;
    B2();
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(3) Using smart pointers for class instance and its members" << std::endl << std::endl;
    B3();
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(4) Converting unique pointers to shared pointers" << std::endl << std::endl;
    B4();
    std::cout << std::endl << "=======================" << std::endl << std::endl;
    std::cout << "(B)(5) Use `weak_ptr` for `shared_ptr` like pointers that can dangle " << std::endl << std::endl;
    B5();
}