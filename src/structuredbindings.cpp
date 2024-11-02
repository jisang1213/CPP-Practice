#include <iostream>
#include <utility> // for std::pair
#include <tuple>

/*
This file demonstrates the usages of structured bindings(C++17) to unpack tuples
*/

std::pair<int, int> get2DCoordinates() {
    return {10, 20};
}

std::tuple<int, int, int> get3Dcoordinates() {
    return {10, 20, 30};
}

int main(){
    // The syntax for structured bindings is as follows:
    // auto [name1, name2, ..., nameN] = expression;

    // With std library pairs (two elements)
    std::pair<int, std::string> person = {25, "Alice"};
    // Typically, you would access pair elements using first and second:
    std::cout << "First: " << person.first << " Second: " << person.second << std::endl;
    // You can unpack the pair using structure bindings:
    auto [age, name] = person;
    std::cout << "Age: " << age << ", Name: " << name << std::endl;

    // With tuples (multiple elements)
    std::tuple<int, double, std::string> data = {42, 3.14, "Hello"};
    auto [x, y, z] = data;
    std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;

    // Structured bindings can unpack arrays as well:
    int arr[3] = {1, 2, 3};
    auto [a, b, c] = arr;
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

    // std::tie and std:make_tuple are useful when packing and unpacking tuples.
    // std::tie makes a lvalue reference to existing variables, without need for copying
    // The syntax is: std::tie(variable1, variable2, ...) = std::make_tuple(value1, value2, ...);

    int X, Y;
    std::tie(X, Y) = get2DCoordinates(); // this assigns the tuple values to x and y
    std::tie(X, Y, std::ignore) = get3Dcoordinates(); // You can use std::ignore to skip elements you don't need.

    // Create a tuple with an int, double, and string using std::make_tuple without specifying the type (type deduction)
    auto myTuple = std::make_tuple(42, 3.14, "Hello");
    // This syntax is simpler than:
    std::tuple<int, double, std::string> myTuple2(42, 3.14, "Hello");
    // or with aggregate initialization syntax:
    std::tuple<int, double, std::string> myTuple3 = {42, 3.14, "Hello"}; // valid from C++17

    // Access elements using std::get
    std::cout << "Integer: " << std::get<0>(myTuple) << "\n";
    std::cout << "Double: " << std::get<1>(myTuple) << "\n";
    std::cout << "String: " << std::get<2>(myTuple) << "\n";

}