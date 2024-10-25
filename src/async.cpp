#include <iostream>
#include <future>
#include <chrono>

int asyncTask(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work
    return x * 2; // Return result
}

int main() {
    std::future<int> result = std::async(std::launch::async, asyncTask, 5); // Start async task

    std::cout << "Doing other work while waiting...\n";

    // Get the result (will block until the result is ready)
    int value = result.get(); 
    std::cout << "Result from async task: " << value << '\n';

    return 0;
}
