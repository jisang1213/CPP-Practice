#include <iostream>
#include <vector>
#include <functional>
#include <format> // C++20

// TODO: default arguments, inline functions, function overloading, function templates

void HelloWorld(){
    std::cout << "Hello world" << std::endl;
}

int add(int a, int b){
    return a+b;
}

// Raw function pointer argument
void for_each(const std::vector<int>& vec, void(*callback)(int a)){
    for(int x : vec){
        callback(x);
    }
}

// std::function - syntax: std::function<return_type(arg1_type, arg2_type, ..)>
void for_each2(const std::vector<int>& vec, const std::function<void(int)>& callback){
    for(int x : vec){
        callback(x);
    }
}

void print(int x){
    std::cout << x << std::endl;
}

int main(){

    // Assign the function to a name
    auto func1 = HelloWorld; // You can also do &HelloWorld
    func1();

    // Alternative, explicity write the type
    void(*func2)() = HelloWorld; 
    func2();

    // For a function with a return type and or arguments, do this:
    int(*op1)(int, int) = add; // return_type(*name)(arg_type, ..)
    std::cout << "Sum of 1 and 2 is: " << op1(1,2) << std::endl;

    // Create an alias using typedef
    typedef void(*Function)();
    Function func3 = HelloWorld;
    func3();

    // Create an alias with 'using'
    using Operation = int(*)(int, int);
    Operation op2 = add;
    std::cout << "Sum of 3 and 4 is: " << op2(3,4) << std::endl;

    // We can pass a function pointer as an argument to another function (callback)
    std::cout << "Print the elements in vec: " << std::endl;
    std::vector<int> vec = {1,2,3,4,5,6};
    for_each(vec, print); // print is the callback function

    // We can also pass in lambdas
    std::cout << "Print the squares of elements in vec: " << std::endl;
    for_each(vec, [](int x){ std::cout << x*x << std::endl;}); // print is the callback function

    // If we want to capture anything, we need to use the std::function version (for_each2)
    int a = 3;
    std::cout << "Printing the elements in vec added by " << a << ":" << std::endl;
    for_each2(vec, [=](int x){std::cout << a + x << std::endl;}); // print is the callback function

    // std::bind binds arguments to functions
    std::cout << "std::bind without reference wrapper" << std::endl;
    int i = 5;
    const auto f = std::bind(print, i);
    f(); // This calls print(i)
    i++;
    f(); // This still calls print(5)

    // If we want f to track the value of i, we need to wrap it with std::ref
    std::cout << "std::bind without reference wrapper" << std::endl;
    i=5;
    const auto g = std::bind(print, std::ref(i));
    g(); // This calls print(i)
    i++;
    g(); // This still calls print(5)

    // std::placeholder 
    std::cout << "std::placeholder with add(a, b)" << std::endl;
    int arg1 = 10;
    const auto h = std::bind(add, arg1, std::placeholders::_1); // placeholders should be in the order they will be passed in
    // Note: for template functions, we need to specify the type - e.g. add<double>
    std::cout << h(1) << std::endl; // This prints add(10,1)
    std::cout << h(2) << std::endl; // This prints add(10,2)
}