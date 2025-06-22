#include<vector>
#include<iostream>
#include<ranges>

// Some use cases of variadic templates (C++20) and unary and binary fold expressions (C++17)

// Get the sum of arguments
template<typename... Values>
auto sum(Values&&  ... values){
    return (values + ... + 0);
}

// Find the average V1
template<typename T, typename... Ts>
auto average(T value, Ts... values){
    auto n_values = (1. + sizeof...(values));
    return ((value/n_values) + ... + (values/n_values));
}
// Find the average V2
template<typename... Values>
auto average2(Values... values){
    auto sum = (0.0 + ... + values);
    auto n_values = static_cast<double>(sizeof...(values));

    if(n_values == 0){
        throw std::invalid_argument("There must be at least one argument");
    }

    return sum/n_values;
}

// Generic push_back for containers
template<typename Container, typename... Values>
void push_back(Container& container, Values&&... values){
    (container.push_back(std::forward<Values>(values)), ...);
}

template<typename F, typename... Values>
void apply_to_each(F function, Values&&... values){
    (function(std::forward<Values>(values)), ...);
}

using namespace std;

int main(){
    cout << "Sum of numbers 1 to 5: " << sum(1,2,3,4,5) << endl;
    cout << "Average of numbers from 1 to 5: " << average(1,2,3,4,5) << endl;
    cout << "Average of numbers from 1 to 5: " << average2(1,2,3,4,5) << endl;

    vector<int> vec;

    // Push back using fold expressions
    push_back(vec, 1,2,3,4,5);
    for(const auto& x : vec){
        cout << x << ", ";
    }
    cout << "\n";

    // Apply to each using fold expressions
    apply_to_each([](string_view s){ cout << s << " "; }, "Hello", "World", "!");
    cout << "\n";

    // Pushback using apply to each
    apply_to_each([&](int i){ vec.push_back(i); }, 6, 7, 8, 9);
    for(const auto& x : vec){
        cout << x << ", ";
    }
    cout << "\n";
}