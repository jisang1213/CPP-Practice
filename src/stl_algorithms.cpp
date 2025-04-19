#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

/* This file demontrates STL algorithms

Non-Modifying Algorithms:

std::find	Finds the first occurrence of a value in a range.	
std::find(vec.begin(), vec.end(), 5);

std::find_if Finds the first occurent of a value that matches a predicate in a range.
std::find_if(vec.begin(), vec.end(), [](int x){ return x % 2 == 0});

std::count	Counts the occurrences of a value in a range.	
std::count(vec.begin(), vec.end(), 5);

std::all_of	Checks if all elements satisfy a condition.	
std::all_of(vec.begin(), vec.end(), [](int x){ return x > 0; });

std::any_of	Checks if any element satisfies a condition.	
std::any_of(vec.begin(), vec.end(), [](int x){ return x == 5; });

std::none_of	Checks if no element satisfies a condition.	
std::none_of(vec.begin(), vec.end(), [](int x){ return x < 0; });


Modifying Algorithms:

std::copy	Copies elements from one range to another.	
std::copy(src.begin(), src.end(), dest.begin());

std::transform	Applies a function to each element in a range.	
std::transform(vec.begin(), vec.end(), vec.begin(), [](int x){ return x*2; });

std::fill	Fills a range with a specific value.	
std::fill(vec.begin(), vec.end(), 0);

std::replace	Replaces occurrences of a value with another.	
std::replace(vec.begin(), vec.end(), 5, 10);

std::remove	Removes elements matching a value (logical removal).	
std::remove(vec.begin(), vec.end(), 5);


Other Algorithms:

std::for_each operates on each element in a range.
std::for_each(vec.begin(), vec.end(), [](int &n){n*=2;});

std::accumulate	Computes the sum of elements in a range.	
std::accumulate(vec.begin(), vec.end(), 0);

std::adjacent_find	Finds the first pair of adjacent equal elements.	
std::adjacent_find(vec.begin(), vec.end());

std::unique	Removes duplicate consecutive elements.	
std::unique(vec.begin(), vec.end());

std::min_element	Finds the smallest element in a range.	
std::min_element(vec.begin(), vec.end());

std::max_element	Finds the largest element in a range.	
std::max_element(vec.begin(), vec.end());
std::max_element(vec.begin(), vec.end(), [](const int& a, const int& b){ return a < b; }); // With custom comparator
*/

void print(std::vector<int>& vec){
    for (const auto& x : vec){
        std::cout << x << ", ";
    }
    std::cout << std::endl; 
}

int main(){
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    // Find the first instance of 5
    auto it = std::find(vec.begin(), vec.end(), 5);
    // Modify the value of iterator:
    if(it != vec.end()){
        *it = 19;
    }
    print(vec);

    // Find the first element that matches a predicate
    it = std::find_if(vec.begin(), vec.end(), [](int x){ return x % 2 == 0; }); // First even number
    if(it != vec.end()){
        std::cout << "First even number is: " << *it << std::endl;
    }

    // Use of std::count
    auto count = std::count(vec.begin(), vec.end(), 10);
    std::cout << "Number of 10's : " << count << std::endl;

    // You can also use std::count with std::string to iterate over the characters
    std::string str = "Hello my name is Bob";
    count = std::count(str.begin(), str.end(), 'l'); 
    std::cout << "Number of l's : " << count << std::endl;

    // Use of std::all_of
    bool positive = std::all_of(vec.begin(), vec.end(), [](int x){return x>0;});
    std::cout << "Every element is positive: " << std::boolalpha << positive << std::endl;

    // Uses of std::any_of, std::none_of is similar

    // Use of std::copy
    std::vector<int> dest(10);
    std::copy(vec.begin(), vec.end(), dest.begin());
    print(dest);

    // Use of std::tranform for unary operator (one vector to one)
    std::vector<int> squares(vec.size());
    std::transform(vec.begin(), vec.end(), squares.begin(), [](int x){return x*x;});
    print(squares);

    // Use of std::tranform for binary operator (two vectors to one)
    std::vector<int> sum(vec.size());
    std::transform(vec.begin(), vec.end(), dest.begin(), sum.begin(), [](int a, int b){return a+b;});
    print(sum);

    // Use of std::fill
    std::fill(vec.begin(), vec.end(), 0);
    print(sum);

    // Use of std::replace (replaces all instances of 0 with 2)
    std::replace(vec.begin(), vec.end(), 0, 2);
    print(vec);

    // Use of std::remove
    auto new_end = std::remove(squares.begin(), squares.end(), 4);
    print(squares);

    // Now erase the invalid entries at the ends
    squares.erase(new_end, squares.end());
    print(squares);

    // Use of std::for_each to double each element in an vector
    std::for_each(vec.begin(), vec.end(), [](int& n){n*=2;});
    print(vec);

    // Use of acculumate
    auto accum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "The sum is " << accum << std::endl;

    // You can also multiply all elements
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    // Multiply all elements, starting with an initial value of 1
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, [](int a, int b) {
        return a * b; // a is the accumulated value and b is the element in the range
    });
    std::cout << "The product from 1 to 5 is " << product << std::endl;

    // You can also combine strings:
    std::vector<std::string> words = {"Hello", " ", "World", "!"};
    // Concatenate all strings
    std::string sentence = std::accumulate(words.begin(), words.end(), std::string(""));
    std::cout << "Concatenated string: " << sentence << '\n';

    // Use of std::unique to remove consecutive duplicates
    vec = {1, 1, 2, 3, 3, 4, 4, 4, 5};
    new_end = std::unique(vec.begin(), vec.end());
    // Print the range after removing duplicates
    std::cout << "After std::unique: ";
    print(vec);

    // To completely remove duplicates from the container
    vec.erase(new_end, vec.end());
    std::cout << "Final vector: ";
    print(vec);

    // Use of std::min_element and std::max_element
    auto min_it = std::min_element(vec.begin(), vec.end());
    if(min_it != vec.end()){
        std::cout << "Smallest element: " << *min_it << '\n';
    }

    auto max_it = std::max_element(vec.begin(), vec.end());
    if(max_it != vec.end()){
        std::cout << "Smallest element: " << *max_it << '\n';
    }

    // Use of std::adjacent_find
    vec = {1, 2, 3, 3, 4, 5, 5, 6};
    print(vec);
    // Find the first pair of adjacent equal elements
    it = std::adjacent_find(vec.begin(), vec.end());
    if (it != vec.end()) {
        std::cout << "First pair of adjacent equal elements: " << *it << '\n';
    } else {
        std::cout << "No adjacent equal elements found.\n";
    }

    // We can also define a custom predicate
    vec = {1, 3, 2, 4, 6, 5};
    it = std::adjacent_find(vec.begin(), vec.end(), [](int a, int b) {
        return b > a;
    });

    if (it != vec.end()) {
        std::cout << "First adjacent pair where the second is greater: "
                  << *it << " and " << *(it + 1) << '\n';
    } else {
        std::cout << "No such pair found.\n";
    }
}