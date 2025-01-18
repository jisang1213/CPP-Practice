#include <iostream>

/*
This file demonstrates the concept of scope and namespaces in C++
*/

// Static global variables are accessible from on the translatio unit in which they are defined
int a = 12; // global variable
// To access global variables defined in another translation unit, use the keyword extern
// extern int a;

// static int a = 1; // This will shadow the global variable above and cause an error
static int b = 2; // b is only accessible from this file

// Variables define inside a function are local to that function
int nonstatic(){
    int a = 0; // Can only we accessed inside func(). Its lifetime is the duration of the function
    a++;
    return a;
}
// Static variables are variables whose lifetime is not limited to the function (stored in data segment)
int Static(){
    static int a = 0; // a is still alive after func2() ends
    a++;
    return a;
}

/* Namespace scope
A namespace in C++ allows for grouping of functions, classes, and variables under a specific name 
to avoid name conflicts. The scope of a variable or function defined within a namespace is limited 
to that namespace.
*/

namespace example1{
    int x = 3;
}

namespace example2{
    int y=10;
}

// namespaces can be nested
namespace example3{
    namespace example4{
        int x = 4;
    }
}

using namespace example2;

int main(){
    // Global variables
    std::cout << "The value of a is: " << a << std::endl; // This will print 12

    // Non-static local variable is reset every call
    std::cout << "Non-static a: " << nonstatic() << std::endl; // This will print 12
    std::cout << "Non-static a: " << nonstatic() << std::endl; // This will print 12
    std::cout << "Non-static a: " << nonstatic() << std::endl; // This will print 12

    // Static local variable is not reset every call
    std::cout << "Static a: " << Static() << std::endl; // This will print 12
    std::cout << "Static a: " << Static() << std::endl; // This will print 12
    std::cout << "Static a: " << Static() << std::endl; // This will print 12

    // We can directly access y in namespace example2 since we declared that we are using namespace example2
    std::cout << "The value of y is: " << y << std::endl;
    // If we declare another local variable named y, it will shadow the variable y in namespace example2
    int y = 20;
    std::cout << "The value of y is: " << y << std::endl; // This will print 20

    int x = 0;
    std::cout << x << std::endl; // This will print 0
    std::cout << example1::x << std::endl; // This will print 3
    std::cout << example3::example4::x << std::endl; // This will print 4

    // Block scope(enclosed by {}): variables declared inside a block are only accessible from inside the block
    {
        int x = 1;
    }    
    // x is not accessible here - uncommenting the following line will create an error
    // x++;

    // You can define a new variable with the same name inside a scope
    {
        // Redefine x here. This new variable will shadow the x defined outside of this block
        int x = 2;
        // This will print 2
        std::cout << x << std::endl;
    }
}