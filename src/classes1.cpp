#include <iostream>
#include <string>

// This file demonstrates basic concepts in classes in C++
// classes2.cpp demonstrates more advanced concepts such as virtual functions and inheritance

/*
Topic covered in the classes1.cpp file:
- Public, private and protected members
- Naming conventions for member variables
- Private, protected, public inheritance
- Constructors and destructors
- Initializer list in constructor
- Overloaded constructors
- Explicit keyword for disabling implicit conversions
- Operator overloading
- Friend classes and functions
- Static members and functions
*/

// Classes are user-defined data types that can have data members and member functions
class Car{
// Public means that the member is accessible from outside the class through an object of the class
// Protected means that the member is accessible from within the class and from the derived class
// Private means that the member is accessible only from within the class (default if not specified)
public:
    // Constructors are special member functions that are called when an object is created
    Car(std::string owner): owner_(owner){ // Initializer list
        std::cout << "Car created" << std::endl;
    }
    // Destructors are special member functions that are called when an object is destroyed
    ~Car(){
        std::cout << "Car destroyed" << std::endl;
    }
    void print(){
        std::cout << "This is a car" << std::endl;
    }

    void getOwner(){
        std::cout << "Owner: " << owner_ << std::endl;
    }

protected:
    std::string owner_; // Naming convention for member variables: end with underscore

private:
    int x;
};

// Derived class inherits the members of the base classs
// The access level specifier can be public, protected or private (private by default)
// It specifies the maximum access level for the inherited members
class Audi : public Car{
public:
    // explicit keyword disables implicit conversions
    explicit Audi(std::string owner): Car(owner){
        std::cout << "Audi created" << std::endl;
    }
    // Redefining a base class function that is not declared as virtual hides the base class definition
    // The function to call is determined at compile time based on the type of the pointer
    void print(){
        std::cout << "This is an Audi" << std::endl;
    }
};

class Mercedes : protected Car{
public:
    void print(){
        std::cout << "This is a Mercedes" << std::endl;
    }
};

class Porshce : private Car{
public:
    void print(){
        std::cout << "This is a Porshce" << std::endl;
    }
};

int main(){
    Audi audi("Bob");
    audi.print();
    audi.getOwner();

    // Assigning derived class object to base class pointer
    Car* car = new Audi("John");
    // Car* car = new Mercedes(); // Not allowed due to protected inheritance
    // Car* car = new Porshce(); // Not allowed due to private inheritance
    car->print(); // This calls the base class print() due to static binding
    delete car;

    // 2. Explicit constructors
    // Person p("John", 25); // Direct initialization
    // Person p1 = Person("John", 25);  // OK: Explicit constructor call
    // Person p2 = Person(25);  // OK: Explicit constructor call
    // Person p3 = "John";  // Error: Cannot convert const char* to Person
    // Person p4 = 25;  // Error: Cannot convert int to Person
}