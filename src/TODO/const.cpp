#include <iostream>
#include <stdexcept>

/*
This file demonstrates the usage of the const keyword
const values, const references, const pointers, const functions, const operators, const return types

It also demonstrates the concept of const correctness

An examples of the constexpr keyword is also shown
*/


// constexpr is a keyword that specifies that a function or variable can be evaluated at compile time. 
constexpr int square(int x) {
    return x * x;
}
constexpr int value = square(5); // Evaluated at compile time


class MyVector {
private:
    int* data;      // Pointer to hold the dynamic array
    size_t size;    // Number of elements in the array

public:
    // Constructor accepting an initializer list
    MyVector(std::initializer_list<int> init) : size(init.size()) {
        data = new int[size];
        size_t index = 0;
        for (const int& value : init) {
            data[index++] = value;
        }
    }

    // Destructor to free allocated memory
    ~MyVector() {
        delete[] data;
    }

    // Non-const operator[] for modifying elements
    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Const operator[] for read-only access
    const int& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};

int main() {
    MyVector myVec = {1, 2, 3, 4, 5};

    // Modify an element
    myVec[2] = 10; // Calls non-const version
    std::cout << "Modified element at index 2: " << myVec[2] << std::endl; // Outputs: 10

    // Read-only access
    const MyVector constVec = {6, 7, 8, 9, 10};
    std::cout << "Element at index 1 from const object: " << constVec[1] << std::endl; // Outputs: 7

    return 0;
}
