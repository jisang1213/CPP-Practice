#include <iostream>
#include <utility>
#include <string>
/*
This files covers the concepts of lvalues and rvalues, and forwarding references
lvalues are named values with a location in memory that can exist on the left hand side of a = operator
rvalues are temporary, disposable values

rvalues can be categorized into prvalues (pure rvalues) and xvalues (expiring values)

prvalues represent temporary values that are not associated with any identifiable memory location.
e.g. int x = 2; '2' here is a prvalue

xvalues represent objects that can be "moved from" (their resources can be transferred to another object).
Usually the result of calling std::move or a function that returns an rvalue reference.
e.g. int x = 10;
int&& y = std::move(x); `std::move(x)` is an xvalue
*/

void foo(int& x) {
    std::cout << "Non-const lvalue reference: " << x << "\n";
}

void foo(int&& x) {
    std::cout << "Rvalue reference: " << x << "\n";
}

void foo(const int& x) {
    std::cout << "Const lvalue reference: " << x << "\n";
}

void bar(int& x){
    std::cout << "bar() lvalue reference: " << x << "\n";
}
void bar(int&& x){
    std::cout << "bar() received rvalue reference: " << x << "\n";
}

// Forwarding (universal) reference - only use if you have to because it results in mode code generation
template <typename T>
void foo(T&& x){
    std::cout << "Forwarding reference: " << x << "\n";
    bar(std::forward<T>(x)); // Perfectly forward the arg (either rvalue or lvalue) to another function
}

class Person{
    std::string name_;
public:
    Person(std::string name) : name_(name) {
        std::cout << "Person constructor called with name: " << name << "\n";
    }
};

void func(Person& person){
    std::cout << "func(Person&) called" << "\n";
}
void func(const Person& person){
    std::cout << "func(const Person&) called" << "\n";
}
void func(Person&& person){
    std::cout << "func(Person&&) called" << "\n";
}

int main() {
    int a = 10;      // 'a' is an lvalue
    const int b = 15; 
    
    std::cout << "foo(a) - ";
    foo(a);          // Calls `foo(int&)` - binds to non-const lvalue reference
    std::cout << "foo(20) - ";
    foo(20);         // Calls `foo(int&&)` - binds to rvalue reference
    std::cout << "foo(std::move(a)) - ";
    foo(std::move(a)); // Calls `foo(int&&)` - binds to rvalue reference
    std::cout << "foo(b) where b is const - ";
    foo(b);          // Calls `foo(const int&)` - binds to const lvalue.

    // Special case:
    int x = 10;
    int&& r = x + 5; // r binds to the temporary value produced by `x + 5`

    std::cout << "foo(r) where r is int&& - ";
    foo(r);          // Calls `foo(int&)` because `r` is an lvalue
    std::cout << "foo(std::move(r)) where r is int&& - ";
    foo(std::move(r)); // Calls `foo(int&&)` because `std::move(r)` makes it an rvalue 
    /*
    r is a named rvalue reference.
    While r itself is an lvalue (because it has a name and can be referred to), the value it refers to is an rvalue.
    If you try to pass r to a function that has an int&& overload, you must use std::move(r) to treat it as an rvalue again.
    */

    std::cout << "foo<int&&>(40) - ";
    foo<int&&>(40); // explicitly forces the template and called foo(T&&)

    func(Person("Joe")); // This calls func(Person&&) because it is a temporary (rvalue)
    Person Bob("Bob");
    func(Bob); // This calls func(Person&) because it is a lvalue
    func(std::move(Bob)); // This calls func(Person&&) because Bob is an expiring value
    // Bob is left in a valid but unspecified state
}
