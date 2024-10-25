#include <iostream>
#include <thread>
#include <cstdint>
#include <mutex>
#include <chrono>

uint64_t some_global_var = 0;
std::mutex mut;

void increment(){
    std::lock_guard<std::mutex> lock(mut);
    for(int i=0; i<1000000; i++){
        some_global_var++;
        // mut.unlock(); //swap 1 to 0

        //Some code that is irrelevant to changing glovar var
        // 1000 lines of code

        // mut.lock();
        // // changing global variable
        // mut.unlock();
    }
}

int main(){

    // Measure the time taken by a code block
    auto start = std::chrono::high_resolution_clock::now(); // Start time
    // This is slower but it runs in parallel
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now(); // End time
    // Calculate the duration in microseconds
    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout << "Execution time for parallel: " << duration.count() << " microseconds" << std::endl;


    // Measure the time taken by a code block
    start = std::chrono::high_resolution_clock::now(); // Start time
    // This is faster but it runs in series
    increment();
    increment();
    end = std::chrono::high_resolution_clock::now(); // End time
    // Calculate the duration in microseconds
    duration = end - start;
    std::cout << "Execution time for series: " << duration.count() << " microseconds" << std::endl;
}


