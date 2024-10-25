#include <concepts>
#include <iostream>

// Functon templates
template <typename T> // T is a place holder for any type
requires std::integral<T> // C++ 20 template constraints
T add(T a, T b){
    return a+b;
}

// You can also define a concept (template constraint)
template <typename T>
concept Integral = std::integral<T>;

template <Integral T>
T sub(T a, T b){
    return a-b;
}

// Template classes with generic type
template <typename T>
class MyClass {
public:
    void info() { std::cout << "Generic version\n"; }
};

// Full specialization for type int
template <>
class MyClass<int> {
public:
    void info() { std::cout << "Specialized version for int\n"; }
};

// Full specialization for type double
template <>
class MyClass<double> {
public:
    void info() { std::cout << "Specialized version for double\n"; }
};

// Template class with multiple types
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair(T1 first, T2 second): first(first), second(second) {}

    T1 getfirst() const{
        return first;
    }
    T2 getsecond() const {
        return second;
    }
    void print(){
        std::cout << "first: " << first << ", second: " << second << std::endl;
    }
};

// Partial specialization for when both T1 and T2 are same types
template <typename T>
class Pair<T,T> {
private:
    T first;
    T second;
public:
    Pair(T first, T second): first(first), second(second) {}

    T getfirst() const{
        return first;
    }
    T getsecond() const {
        return second;
    }
    void print(){
        std::cout << "first: " << first << ", second: " << second << " (same types)" << std::endl;
    }
};


// Variadic templates (introduced in C++11)
// Base case (only one arg)
template <typename T>
void print(T arg){
    std::cout << arg << std::endl;
}
// Use typename... Args for types or Args... args for values
template <typename T, typename... Args>
void print(T arg1, Args... args){
    std::cout << arg1 << ", ";
    print(args...);
}

// Example of tuple class that can hold variable number of elements of different types:
// Base case: Empty tuple
template <typename... Values>
class Tuple;

// Specialization for one value
template <typename T, typename... Rest>
class Tuple<T, Rest...> {
    T value;
    Tuple<Rest...> rest;

public:
    Tuple(T val, Rest... restVals) : value(val), rest(restVals...) {}

    T getValue() const {
        return value;
    }

    const Tuple<Rest...>& getRest() const {
        return rest;
    }
};

// Specialization for no values (end of recursion)
template <>
class Tuple<> {};

// Expanding a parameter pack for sum example
// Base case
template <typename T>
T sum(T value){
    return value;
}
// Recursive case
template <typename T, typename... Rest>
T sum(T value, Rest... rest){
    return value + sum(rest...);
}

// Fold expressions simplify varidiac template functions (C++17)
template <typename... Args>
auto sum_fold(Args... args){
    return (... + args);
}

int main(){
    std::cout << add(1,2) << std::endl; 
    std::cout << sub(1,2) << std::endl;

    MyClass<long> instance1;
    MyClass<int> instance2;
    MyClass<double> instance3;

    instance1.info();
    instance2.info();
    instance3.info();

    Pair pair1(1.0, "hello");
    pair1.print();

    Pair pair2(1.0, 2.0);
    pair2.print();

    print(1,2,3,4,5, "last argument");

    Tuple<int, double, std::string> myTuple(42, 3.14, "Hello");
    std::cout << myTuple.getValue() << std::endl; // Output: 42
    std::cout << myTuple.getRest().getValue() << std::endl; // Output: 3.14
    std::cout << myTuple.getRest().getRest().getValue() << std::endl; // Output: Hello

    std::cout << "The sum from 1 to 5 is (recursion): " << sum(1,2,3,4,5) << std::endl;
    std::cout << "The sum from 1 to 5 is (fold expression): " << sum_fold(1,2,3,4,5) << std::endl;

    return 0;
}