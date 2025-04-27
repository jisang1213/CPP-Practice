#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>

/*
std::ranges was introduced in C++20
*/

int main(){
    std::vector<int> v = {5, 3, 1, 4, 2};
    // Before C++20, we had to sort like this:
    std::sort(v.begin(), v.end());
    // With ranges we can do
    std::ranges::sort(v); // no need for begin() / end()
    for (int x : v)
        std::cout << x << " ";
    std::cout << std::endl;
    
    // Views are a lazy way of transforming ranges without copying data
    v = {1,2,3,4,5,6};
    // Data flows from left of the pipe operator (|) to the right
    auto even = v | std::ranges::views::filter([](int n) { return n % 2 == 0; }); // You can use the shorter alias std::views instead
    for (int x : even)
        std::cout << x << " ";  // prints: 2 4 6
    std::cout << std::endl;
    
    auto result = v 
    | std::views::filter([](int x) { return x % 2 == 0; })
    | std::views::transform([](int x) { return x * x; });
    for (int x : result)
        std::cout << x << " ";  // prints: 2 4 6
    std::cout << std::endl;
    

    v = {1,2,3,4,5,6,7,8,9,10};
    for (int x : v 
        | std::views::drop(3)   // drop first 3 elements: 4,5,6,7,8,9,10
        | std::views::take(4)   // take first 4 of those: 4,5,6,7
        | std::views::transform([](int x){ return x*10; }) // multiply by 10
    ){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // std::views::iota is a sequence of numbers starting from the argument (++ is called for next element)
    for (int x : std::views::iota(0) 
           | std::views::filter([](int n){ return n % 3 == 0; })
           | std::views::take(5))
    std::cout << x << ' ';  // 0 3 6 9 12
    std::cout << std::endl;

    // std::views::iota(s) → all integers from s upward.
    // std::views::iota(s,e) → integers in [s, e).

    for(int x : std::views::iota(1,5)){
        std::cout << x << ' '; // 1 2 3 4
    }
    std::cout << std::endl;

    // Subranges
    std::ranges::sort(std::ranges::subrange(v.begin() + 1, v.begin() + 5));
}