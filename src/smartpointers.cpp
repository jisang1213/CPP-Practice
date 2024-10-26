#include <iostream>
#include <memory>  // Required for smart pointers

/*
Smart pointers help manage memory automatically, reduce the risk of memory leaks, 
and improve code safety and maintainability.

There are 3 different types of smart pointers:
std::unique_ptr: Exclusive ownership, cannot be copied.
std::shared_ptr: Shared ownership, can be copied and tracked with reference counting.
std::weak_ptr: Non-owning reference, used to prevent circular references.
*/

class Person {
public:
    Person(std::string name) : name_(name) {}
    void greet() const {
        std::cout << "Hello, my name is " << name_ << std::endl;
    }

private:
    std::string name_;
};

int main() {
    // Using std::unique_ptr (there can only be one owner)
    std::unique_ptr<Person> person1 = std::make_unique<Person>("Alice");
    person1->greet();

    // To transfer ownership, use std::move()
    std::unique_ptr<Person> newowner = std::move(person1);
    // Now person1 is left in a null state (it no longer owns the object).
    if (!person1) {
        std::cout << "person1 is now null." << std::endl;
    }
    newowner->greet();  // Calls greet() using the new owner

    // Using std::shared_ptr
    std::shared_ptr<Person> person2 = std::make_shared<Person>("Bob");
    person2->greet();


// TODO: std::weak_ptr


    return 0;
}
