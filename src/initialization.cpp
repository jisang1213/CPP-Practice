#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>
/*
This file demonstrates different ways to initilaize objects and modern C++ conventions like
uniform initialization (e.g. int i{};).
*/


int main(){
    /*
    Uniform initialization, introduced in C++11, provides a consistent syntax for initializing objects, 
    including fundamental types, aggregates, and user-defined types. The main goal is to unify the 
    various initialization forms and to help avoid common pitfalls associated with them.
    */
    int a{5};           // Initializes 'a' to 5
    double b{3.14};    // Initializes 'b' to 3.14

    // Zero initialization
    int c{}; // This initializes c to 0

    struct Point {
        int x;
        int y;
    };
    Point p{10, 20};    // Initializes 'p' with x = 10, y = 20

    int arr[]{1, 2, 3}; // Initializes an array of integers

    class MyClass {
    public:
        MyClass(int value) : value1_(value), value2_(value+1) {}
        // Members in the initializer list are initialized in the order declared below not order listed.
    private:
        int value1_;
        int value2_;
    };
    MyClass obj{42};     // Calls the constructor with argument 42

    class MyVector {
    public:
        MyVector(std::initializer_list<int> init) {
            // Handle initialization using range based for-loop
            for(const int& x : init){
                vec_.push_back(x);
            }
            // Alternative we can use iterators explicitly (effectively same from compiler perspective)
        }
    private:
        std::vector<int> vec_; // Inner container just for sake of simplicity
    };
    MyVector vec{1, 2, 3, 4}; // Initializes MyVector with an initializer list

    // Uniform initialization (or brace initialization) does not allow narrowing conversion (loss of info)
    // int z{3.14}; // Error: narrowing conversion
    // To do this you need to explicitly cast it to an int
    int z{static_cast<int>(3.14)};

    std::string str1{"hello world"};

    std::string str2{std::move(str1)}; // Move constructor called here
    std::string str3 = std::move(str2); // Move constructor called here since str3 is undeclared 
    
    str1 = std::move(str3); // Move assignment operator called here
}