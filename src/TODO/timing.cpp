#include <chrono>
#include <iostream>

// How to time code in C++

void count_to(int n){
    int x=0;
    for (int i = 0; i < n; i++) {
        x++;
    }
}

int main(){

    auto start = std::chrono::high_resolution_clock::now();
    // Code to be timed
    count_to(1000000);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}