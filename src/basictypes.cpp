#include <iostream>
#include <cstdio>

/*
This file demonstrates the usage of the types in C++

Topics include:
- Primitive types
- User-defined types
- Pointers
- References
- Arrays
- Typedefs
- Auto

*/

// main() is the entry point of the program - it returns 0 to indicate successful execution, and a non-zero value to indicate an error
int main(int argc, char* argv[]) {
    // argc is the number of command-line arguments passed to the program
    // argv is an array of strings containing the command-line arguments

    // In C++, we can use std::cout to print output to the console
    std::cout << "Hello, World!" << std::endl;

    // Primitive types (and many more)
    int integer = 10;
    float floatingPoint = 3.14;
    double doublePrecision = 3.14159;
    char character = 'A';
    bool boolean = true;

    // Void type (generic pointer that can point to any type)
    void* voidPointer = nullptr; // 'nullptr' is a null pointer constant
    // *voidPointer = 10; // This will cause a compilation error because void pointers cannot be dereferenced

    // User-defined types
    struct Point {
        int x;
        int y;
    };
    // Alias for a user-defined type
    typedef Point Coordinate;
    // Now we can use the alias 'Coordinate' instead of 'Point'
    Coordinate point = {1, 2};

    // Alternatively, use the 'using' keyword for aliasing
    using Coordinate2 = Point;
    // Or use the alias 'Position' instead of 'Point'
    Coordinate2 position = {3, 4};

    // We can use the dot operator to access the members of a struct
    std::cout << "Point: (" << point.x << ", " << point.y << ")" << std::endl;

    // Or, if we have a pointer to the struct, we can use the -> operator (which is equivalent to (*ptr).)
    Coordinate* pointPtr = &point;
    std::cout << "Point: (" << pointPtr->x << ", " << pointPtr->y << ")" << std::endl;
    // Same as:
    std::cout << "Point: (" << (*pointPtr).x << ", " << (*pointPtr).y << ")" << std::endl;

    // References
    int& ref = integer; // Use '&' to create a reference to a variable
    ref++; // This will increment 'integer' by 1

    // Pointers
    int* ptr = &integer; // Use '&' to get the address of a variable
    *ptr = 20; // Use '*' to dereference (get the value at memory address) a pointer and modify the value it points to

    // Arrays (size must be known at compile time)
    int numbers[5] = {1, 2, 3, 4, 5};
    char name[6] = "Alice"; // Note: The size of the array is 6 to accommodate the null terminator '\0'

    // In C/C++ a string is just a pointer to the first character of the string
    char* namePtr = name;

    // Typically we use std::string for strings in C++
    std::string nameStr = "Alice";

    // Auto keyword - Compiler will infer the type of the variable
    auto a = 10; // Compiler will infer the type of 'a' as int
    auto b = 3.14; // Compiler will infer the type of 'b' as double
    auto nameAuto = "Alice"; // Compiler will infer the type of 'nameAuto' as const char*
    auto nameStrAuto = std::string("Alice"); // Compiler will infer the type of 'nameStrAuto' as std::string

    printSumto(10);

    // Function to increment the value of a variable using pass by reference, pointer, and value
    int i=0;

    increment_ref(i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 1

    increment_ptr(&i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 2

    increment_val(i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 2 (no change)
}

// Function to get the sum of numbers from 0 to n (returns int)
int getSumto(int n){
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
    std::cout << "Sum: " << sum << std::endl;
}

// void is a special data type that indicates the absence of a value
void printSumto(int n){
    int sum = getSumto(n);
    std::cout << "Sum: " << sum << std::endl;
}

// Pass by reference
void increment_ref(int &n) { //takes an integer reference as an argument and increments it by 1
    n++; // This will increment the value of the variable passed to the function
}

// Pass by pointer
void increment_ptr(int *n) { //takes an integer pointer as an argument and increments the value it points to by 1
    (*n)++; // This will increment the value at the memory address pointed to by the pointer
}

void increment_val(int n) { //takes an integer as an argument and increments it by 1
    n++; // This will increment a copy of the variable passed to the function
}