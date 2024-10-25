#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void incrementCounter(int id) {
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        ++counter; // Critical section
    }
    std::cout << "Thread " << id << " finished.\n";
}

int main() {
    std::thread t1(incrementCounter, 1);
    std::thread t2(incrementCounter, 2);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << '\n';
    return 0;
}
