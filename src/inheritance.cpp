#include <iostream>

class Base{
public:
    void print(){
        std::cout << "This is the base class" << std::endl;
    }
};
class Derived : public Base{
public:
    // Redefining a base class function that is not declared as virtual hides the base class definition
    // The function to call is determined at compile time based on the type of the pointer
    void print(){
        std::cout << "This is the derived class" << std::endl;
    }
};

class Base_virtual{
public:
    virtual void print(){
        std::cout << "This is the base class" << std::endl;
    }
};
class Derived_virtual: public Base_virtual{
public:
    // Redefining a base class function that is not declared as virtual hides the base class definition
    // The function to call is determined at compile time based on the type of the pointer
    void print() override{
        std::cout << "This is the derived class" << std::endl;
    }
};

// Pure virtual classes
// A pure virtual class in C++ is a class that has at least one pure virtual function

// Abstract base class (pure virtual class)
class Shape {
public:
    // Pure virtual function
    virtual void draw() const = 0;

    // Optional: Virtual destructor to allow proper cleanup of derived objects
    virtual ~Shape() {}
};

// Derived class: Implements Shape interface
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Another derived class: Implements Shape interface
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle" << std::endl;
    }
};

// Base class with a virtual destructor (good practice)
class BaseWithVirtual {
public:
    // Virtual destructor
    virtual ~BaseWithVirtual() {
        std::cout << "BaseWithVirtual destructor called." << std::endl;
    }
};

// Derived class inheriting from BaseWithVirtual
class DerivedWithVirtual : public BaseWithVirtual {
public:
    // Destructor to release resources
    ~DerivedWithVirtual() {
        std::cout << "DerivedWithVirtual destructor called." << std::endl;
    }
};


int main(){

    // std::unique_ptr<Base> base1 = std::make_unique<Base>();
    // std::unique_ptr<Base> base2 = std::move(base1); // R values

    Base* base1 = new Derived();
    base1->print(); // This calls the base class print()

    Base_virtual* base2 = new Derived_virtual();
    base2->print(); // This calls the derived class print() due to virtual dispatch

    delete base1;
    delete base2;

    // Shape s;  // Error: Cannot instantiate an abstract class
    Shape* shape1 = new Circle();   // OK: Using polymorphism
    Shape* shape2 = new Rectangle(); 
    shape1->draw();  // Calls Circle::draw()
    shape2->draw();  // Calls Rectangle::draw()

    delete shape1;
    delete shape2;

    // Example with virtual destructor (correct behavior)
    BaseWithVirtual* virtualPtr = new DerivedWithVirtual();
    delete virtualPtr;  // Correct destruction - both derived and base destructors are called

}