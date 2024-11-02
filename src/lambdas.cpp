#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
/*
This file demonstrates the usages of lambdas(C++11)
*/

// In member functions, you can capture this to access member variables and functions of the class.
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}

    void doSomething() {
        auto lambda = [this]() { return value * 2; }; // Capture this pointer
        std::cout << "Member variable 'value' * 2 is: " << lambda() << std::endl; // Outputs: value * 2
    }
};

int main(){
    /* Lambdas are short, convenient unnamed functions that can be defined inline.
    Their general syntax is as follows:
    [capture](parameters) -> return_type {
    // function body
    }
    */
    // You can capture by value or by reference. To capture by value, just name the variable.
    // To capture by reference add & before the name.
    int x = 10;
    int y = 20;
    auto lambda = [x, &y]() { return x + y; }; // x by value, y by reference
    y = 30; // Changing y changes the captured value
    std::cout << lambda() << std::endl; // Outputs: 40

    // Return type deduction - the return type can be automatically deduced, but you can explicitly specify it for clarity:
    auto divide = [](double a, double b) -> double {
        return a / b;
    };
    std::cout << divide(3.0, 2.0) << std::endl; // Outputs: 1.5

    // You can capture all by value or reference using [=] or [&]

    auto capturebyreference = [&](){return x + y; };
    auto capturebyvalue = [=](){return x + y; };
    x++;
    y++;
    std::cout << capturebyreference() << '\n'; // just print newline to avoid flushing buffer. I/O operations are expensive.
    // Outputs: 42
    std::cout << capturebyvalue() << std::endl;
    // Outputs: 40

    // You can also do capture initialization:
    int a = 5;
    auto captureinit = [b = a + 10]() { return b; }; // b is initialized to a + 10
    std::cout << captureinit() << std::endl; // Outputs: 15

    // Demonstration of capturing this pointer:
    MyClass obj(5);
    obj.doSomething(); // Outputs: 10

    // You can also use lambdas for defining thread behavior:
    int value = 5;
    std::thread t([&value]() {
        value += 10;
        std::cout << "Value in thread: " << value << std::endl; // Outputs: Value in thread: 15
    });

    t.join();
    std::cout << "Value in main: " << value << std::endl; // Outputs: Value in main: 15

    // You can use lambdas with std algorithms:
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int threshold = 5;
    // Find the first number greater than the threshold
    // The type of the lambda's parameter must match the type of the elements in the range being searched.
    auto it = std::find_if(numbers.begin(), numbers.end(), [threshold](int number) {
        return number > threshold;
    });

    if (it != numbers.end()) {
        std::cout << "First number greater than " << threshold << " is " << *it << std::endl;
    } else {
        std::cout << "No number greater than " << threshold << " found." << std::endl;
    }
}