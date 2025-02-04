#include <iostream>
#include <string>

/*
This file demonstrates C++ style casting
*/

// C-style casts

double a = 3.14;
int b = (int)a;
//or
int c = int(a);

// C++ Style Casts:

// static casts are used for compatible types
double x = 3.14;
int y = static_cast<int>(x);  // Converts double to int (truncates decimal part)

/*
Dynamics casts are used to downcast from a base class to a derived class and 
you want to ensure the actual object type before calling derived class-specific functions.
Upcasting is always safe (Derived -> Base)
For dynamic_cast to work, the class must have at least one virtual function.
If the cast fails, dynamic_cast will:
- return nullptr for pointers
- throw a std::bad_cast exception for references
Cast is checked for validity at run time
*/

class Animal {
public:
    virtual void sit() { std::cout << "sat down" << std::endl; }
    void roll() {std::cout << "rolling" << std::endl; }
    virtual ~Animal() {}  // At least one virtual function is required for polymorphism.
};

class Dog : public Animal {
public:
    void sit() override {std::cout << "dog sat down" << std::endl; }
    void roll() {std::cout << "dog rolling" << std::endl; }
    void bark() { std::cout << woof << std::endl; }
private:
    std::string woof = "Woof!";
};

class Cat : public Animal {
public:
    void sit() override {std::cout << "cat sat down" << std::endl; }
    void roll() {std::cout << "cat rolling" << std::endl; }
    void meow() { std::cout << "Meow!\n"; }
};

#include <iostream>
#include <typeinfo>  // For std::bad_cast

void handleAnimal(Animal& animal) {
    try {
        Dog& dogRef = dynamic_cast<Dog&>(animal);  // Safe cast attempt
        dogRef.bark();
    } catch (const std::bad_cast& e) {
        std::cout << "Not a Dog: " << e.what() << '\n';
    }
}

int main(){

    Animal* animal = new Dog();  // A base class pointer holding a derived class object.

    // Dynamic casting (always safe for upcasting, but not for downcasting)
    // Only works with classes that have at least one virtual function. 

    // Attempt to cast the Animal pointer to a Dog pointer.
    Dog* dogPtr = dynamic_cast<Dog*>(animal); // Safe cast attempt

    // Returns nullptr if the cast fails.
    if (dogPtr) {
        dogPtr->bark();  // Safe to call Dog-specific methods.
    } else {
        std::cout << "The cast to Dog failed.\n";
    }

    // Try casting the Animal pointer to a Cat pointer (which will fail).
    Cat* catPtr = dynamic_cast<Cat*>(animal);
    if (catPtr) {
        catPtr->meow();  // This won't be reached.
    } else {
        std::cout << "The cast to Cat failed.\n";
    }
    delete animal;

    // Example with references
    Dog myDog;
    Cat myCat;

    handleAnimal(myDog);  // Works fine, outputs "Woof!"
    handleAnimal(myCat);  // Throws std::bad_cast

    // Upcasting is safe by default, you can just use implicit casting safely
    Animal* animalPtr1 = &myDog;
    Animal* animalPtr2 = dynamic_cast<Animal*>(&myDog);  // this works fine too

    /* For virtual functions in the base class, the correct derived class function will be called
    even if you are using a base class pointer that has been upcast from the derived class due to
    dynamic dispatch and RRTI (runtime type inference) */
    
    animalPtr1->sit(); // this will call sit() of the Dog class due to late binding
    animalPtr1->roll(); // roll() is not declared virtual so it is subject to early (static) binding
    // this will call roll() of the Animal class

    /* Const Cast
    const_cast is used to add or remove the const qualifier from a variable.
    It allows you to modify a constant variable (though this is often discouraged).*/
    const int *x = new int(2);
    int* y = const_cast<int*>(x);  // Removing const
    *y = 42;  // Modifying the value (unsafe)

    // Alternatively you can also cast a non const variable to const
    const int *z = const_cast<const int*>(y); // but this is not needed
    const int *w = y; // this is sufficient
    delete x;

    /* Reinterpret cast
    Uses: Low-Level Programming: When dealing with low-level system programming, 
    hardware interactions, or memory manipulation. It "reinterprets the bits".
    Undefined Behavior: Using reinterpret_cast can lead to undefined behavior if you 
    access memory that the casted pointer does not legally own.
    */
    
    Animal* animalPtr3 = new Animal();

    // Unsafe reinterpret cast from Base* to Derived*
    Dog* dogptr = reinterpret_cast<Dog*>(animalPtr3);

    std::cout << "reintepreted animal as dog" << std::endl;
    // Undefined behavior if derivedPtr is dereferenced
    dogptr->bark(); // This results in undefined behaviour
    myDog.bark(); // This works fine

    delete animalPtr3; // Clean up allocated memory
    
    return 0;
}