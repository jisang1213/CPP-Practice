// #include is a preprocessor directive that tells the compiler to include a header file (.hpp or .h) before compiling the code
#include <iostream>
#include <string>
// #include "some_headerfile.hpp"
// <> means C/C++ standard library, "" means local file (in the same directory or other directories in the include path)

/*
Topics include:
- Function prototypes
- Primitive types
- User-defined types
- Pointers
- References
- Arrays
- Typedefs
- Auto keyword (type deduction)
*/


// Function prototypes (declaration) - functions must be declared before they are used (typically done in a header file)
int getSumto(int n);
void printSumto(int n);
void increment_ref(int &n);
void increment_const_ref(const int &n);
void increment_ptr(int *n);
void increment_val(int n);

// main() is the entry point of the program - it returns 0 to indicate successful execution, and a non-zero value to indicate an error
int main(int argc, char* argv[]) {
    // argc is the number of command-line arguments passed to the program
    // argv is an array of strings containing the command-line arguments
    // argv[0] is the name of the program itself
    // argv[1] is the first argument, argv[2] is the second argument, and so on

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

    // A string is just a null-terminated array of characters
    char name[] = "Alice"; // Note: The size of the array is 6 to accommodate the null terminator '\0'
    name[0] = 'B'; // This will change the first character of the string to 'B'

    // In C/C++ a string is just a pointer to the first character of the string
    char* namePtr = name;
    namePtr[0] = 'C'; // This will change the first character of the string to 'C'

    // Strings in C++ can be represented using the std::string class
    std::string nameStr = "Alice";

    // "const" keyword is used to enforce immutability
    const char* nameConst = "Alice"; // A pointer to a constant string
    // nameConst[0] = 'B'; // This will cause a compilation error because the string is constant

    // If the const is on the right of the *, the pointer is constant, not the value
    char* const namePtrConst = name; // A constant pointer to a string
    namePtrConst[0] = 'D'; // We can still change the value of the string
    // namePtrConst = "Bob"; // But not what it points to

    // Auto keyword - Compiler will infer the type of the variable
    auto a = 10; // Compiler will infer the type of 'a' as int
    auto b = 3.14; // Compiler will infer the type of 'b' as double
    auto nameAuto = "Alice"; // Compiler will infer the type of 'nameAuto' as const char*
    auto nameStrAuto = std::string("Alice"); // Compiler will infer the type of 'nameStrAuto' as std::string

    // Function call (defined below)
    printSumto(10);

    // Function to increment the value of a variable using pass by reference, pointer, and value
    int i=0;

    increment_ref(i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 1

    increment_ptr(&i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 2

    increment_val(i);
    std::cout << "Value of i is: " << i << std::endl; // Output: 2 (no change)
} // End of main function


// Function definitions (implementation)

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
void increment_ref(int &n) {
    n++; // This will increment the value of the variable passed to the function
}

// Pass by const reference (immutable reference)
void increment_const_ref(const int &n) {
    // n++; // This will cause a compilation error because the reference is const
    return;
}

// Pass by pointer
void increment_ptr(int *n) {
    (*n)++; // This will increment the value at the memory address pointed to by the pointer
}

// Pass by value (copy of the variable is passed)
void increment_val(int n) {
    n++; // This will increment a copy of the variable passed to the function
}