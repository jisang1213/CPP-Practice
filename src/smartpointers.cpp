#include <iostream>
#include <memory>  // Required for smart pointers

// Refer to "custom.hpp" for a custom implementation of smart pointers

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

    // std::weak_ptr is used to create a weak(non-owning reference to a shared object)
    {
        struct Node {
            std::shared_ptr<Node> next; // Shared ownership creates a circular reference
            std::shared_ptr<Node> prev; // Shared ownership creates a circular reference
        };

        auto node1 = std::make_shared<Node>();
        auto node2 = std::make_shared<Node>();

        node1->next = node2;
        node2->prev = node1;
    }
    // Memory leak: node1 and node2 cannot be destroyed. To resolve this, use weak_ptr
    {
        struct Node_weak {
            std::shared_ptr<Node_weak> next;       // Shared ownership of the next node
            std::weak_ptr<Node_weak> prev;         // Weak reference to the previous node
            int value;
        };

        auto node3 = std::make_shared<Node_weak>();
        auto node4 = std::make_shared<Node_weak>();

        node3->value = 3;
        node3->next = node4;

        node4->value = 4;
        node4->prev = node3; // Use weak_ptr to break the cycle

        // Shared pointer to node3
        std::cout << "Shared pointer use count: " << node3.use_count() << std::endl;
        // Weak pointer to node3
        std::cout << "Is weak_ptr expired? " << (node4->prev.expired() ? "Yes" : "No") << std::endl;

        // To access the object managed by the weak ptr, use lock()
        if (auto locked = node4->prev.lock()) { // Obtain a shared_ptr
            std::cout << "Locked value: " << locked->value << std::endl;
            std::cout << "Shared pointer use count: " << locked.use_count() << std::endl;
        } else {
            std::cout << "The object no longer exists." << std::endl;
        }
    } // Both node3 and node4 are destroyed when they go out of scope

    // Another example
    std::cout << "Example 2:" << "\n";
    std::shared_ptr<int> shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;

    if (auto locked = weak.lock()) { // Obtain a shared_ptr
        std::cout << "Locked value: " << *locked << std::endl;
    } else {
        std::cout << "The object no longer exists." << std::endl;
    }

    shared.reset(); // Destroy the object 
    //Calling reset() on a weak_ptr just makes it stop observing the shared object

    if (weak.expired()) {
        std::cout << "The object is now expired." << std::endl;
    }

    return 0;
}
