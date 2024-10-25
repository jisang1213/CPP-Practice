#include <iostream>

int doSomething() {
    // Perform some operation
    if (/* an error occurs */) {
        return -1; // Return error code
    }
    return 0; // Success
}

int main() {
    if (doSomething() != 0) {
        std::cerr << "An error occurred!\n";
        return 1; // Indicate failure
    }
    // Continue with program
    return 0;
}