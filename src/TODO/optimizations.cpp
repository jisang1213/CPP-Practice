#include <iostream>

// This file demonstrates some common compiler optimizations including RVO (NRVO and URVO), copy elision, and EBO

struct Test {
    Test() { std::cout << "constructed\n"; }
    Test(const Test&) { std::cout << "copied\n"; }
    Test(Test&&) noexcept { std::cout << "moved\n"; }
    ~Test() { std::cout << "destroyed\n"; }
};

Test make() {
    Test t;
    return t;
}

int main() {
    Test x = make();
}