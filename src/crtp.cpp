#include <iostream>
#include <chrono>
#include <cstdint>
#include <string>

/*
This file demonstatese the use of CRTP(curiously recurring template pattern for static polymorphism)
and compares the performance with dynamic polymorphism

Difference in performance is significant in release build
*/

// Abstract base class version
class Interface {
public:
    virtual void count(uint64_t n) = 0;
    virtual uint64_t getValue() = 0;
};

class Implementation : public Interface {
public:
    Implementation() : counter_(0) {}
    void count(uint64_t n) override {
        counter_ += n;
    }
    uint64_t getValue() override {
        return counter_;
    }

private:
    uint64_t counter_;
};

void RunNormal(Interface* interface){
    constexpr unsigned N = 4000;
    for(unsigned i=0; i<N; ++i){
        for(unsigned j=0; j<i; ++j){
            interface->count(j);
        }
    }
    std::cout << "Result is: " << interface->getValue() << std::endl;
}

// CRTP version
template <typename Derived>
class Base{
public:
    void count(uint64_t n){
        static_cast<Derived*>(this)->count(n);
    }
    uint64_t getValue() {
        return static_cast<Derived*>(this)->getValue();
    }
};

class Derived : public Base<Derived> {
public:
    Derived() : counter_(0) {}

    void count(uint64_t n){
        counter_ += n;
    }
    uint64_t getValue() {
        return counter_;
    }

private:
    uint64_t counter_;
};

template <typename T>
void RunCRTP(Base<T>* obj){
    constexpr unsigned N = 4000;
    for(unsigned i=0; i<N; ++i){
        for(unsigned j=0; j<i; ++j){
            obj->count(j);
        }
    }
    std::cout << "Result is: " << obj->getValue() << std::endl;
}

template <typename T, typename F>
void Benchmark(T& obj, F f, std::string name){
    auto start = std::chrono::high_resolution_clock::now();
    f(&obj);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << "  " << duration.count() << " microseconds" << std::endl;
}

int main(){
    Implementation a{};
    Derived b{};
    Benchmark(a, RunNormal, "Virtual base class");
    std::cout << std::endl;
    Benchmark(b, RunCRTP<decltype(b)>, "CRTP");
}