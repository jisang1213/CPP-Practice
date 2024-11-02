#include <iostream>
#include <stdexcept> // For std::runtime_error and std::exception
#include <cassert> // for assert()
#include <system_error>
#include <vector>
#include <fstream>

// You can define your own exception by inheriting from the std::exception class
class MyCustomException : public std::exception {
public:
    const char* what() const noexcept override {    // should be noexcept to match the virtual method of the base class
        return "My custom exception occurred!";
    }
}; // this class can be thrown

/* Some types of exceptions that can be thrown include:
std::runtime_error
std::logic_error
std::out_of_range
std::invalid_argument
std::length_error
std::bad_alloc
*/

double safedivide(double num, double denom) {
    if(denom==0){
        throw std::runtime_error("division by zero is not allowed");
    }
    return num/denom;
}

int getElement(const std::vector<int>& vec, std::size_t index) {
    if (index >= vec.size()) {
        throw std::out_of_range("Index out of range.");
    }
    return vec[index];
}

void func1(){
    try{
        safedivide(10,0);
    }
    catch(const std::runtime_error& e){ // exception will be caught by this catch block
        std::cerr << "exception caught by func1" << std::endl;
    }
    // if there was no matchng catch block, then the exception would be caught by main
}

void allocatelargearray(){
    // By default, new will throw std::bad_alloc if it fails. 
    // You can change this behaviour by using new (std::nothrow) int[100000000000]
    // This will return a nullptr if it fails
    int * largeArray = new int[1000000000];

    // Always deallocate allocated memory
    delete[] largeArray;
}

void checknum(int num){
    if(num<0){
        throw std::invalid_argument("number must be non negative");
    }
}

void riskyOperation() {
    // Simulating a condition that causes a system error
    throw std::system_error(std::make_error_code(std::errc::invalid_argument), "Invalid argument provided");
}

void assertpositive(int num){
    assert(num>0 && "argument should be positive"); // to add an error message just use && and add the message to the right
}

int main() {
    try{
        safedivide(10,20);
        safedivide(10,0);
    }
    catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }

    std::vector<int> numbers = {1, 2, 3};

    try {
        std::cout << getElement(numbers, 5) << std::endl; // Out of range
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Handle out-of-range error
    }

    // In the case of nested functions with multiple try catch blocks, 
    // the stack is unwinded to find the nearest catch block. For example,
    try {
        func1();
    }
    catch(const std::exception& e){
        std::cerr << "exception is caught from main" << std::endl;
    }

    try{
        allocatelargearray();
    }
    catch(const std::bad_alloc& e){
        std::cerr << e.what() << std::endl;
    }

    try{
        checknum(1);
    }
    catch(const std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
    }
    
    // For handling system errors, we can use the error code:
    try{
        riskyOperation();
    }
    catch(const std::system_error& e){
        std::cerr << "Error code: " << e.code() << " (" << e.code().message() << ")" << std::endl;
    }
    
    /*
    Assertions (assert) are used to verify assumptions during development. 
    If an assertion fails, the program stops with a message. 
    Assertions are removed in production code when compiled with the -DNDEBUG flag. 
    assert is not suitable for handling runtime errors but useful for debugging.
    */
    // assertpositive(-1);
}