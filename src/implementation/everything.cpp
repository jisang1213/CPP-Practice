#include <future>
#include <print>
#include <iostream>
#include <memory>

/*
- Unique/shared pointer implementation
- CRTP/Mixins/spaceship operator
*/

template<typename T>
class unique_ptr {
public:
    // Constructor
    unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}
    // Destructor
    ~unique_ptr(){
        delete ptr;
    }
    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept {
        ptr_ = std::exchange(other.ptr_, nullptr);
    }
    // Move assignment operator
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if(&other == this) return *this;
        delete ptr_;
        ptr_ = std::exchange(other.ptr_, nullptr);
        return *this;
    }
    // Delete copy constructor
    unique_ptr(const unique_ptr& other) = delete;
    // Delete copy assignment operator
    unique_ptr& operator=(const unique_ptr& other) = delete;

    T* get() {
        return ptr_;
    }
    T* get() const {
        return ptr_;
    }
    T* operator->() {
        return ptr_;
    }
    T* operator->() const {
        return ptr_;
    }
    void reset(T* p){
        if(ptr_) delete ptr_;
        ptr_ = p;
    }
    void release(){
        if(ptr_){
            delete ptr_;
            ptr_ = nullptr;
        }
    }

private:
    T* ptr_;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args){
    return unique_ptr<T>(new T(std::forward<Arg>(args)...));
}

class Example{
public:
    explicit Example(int x) : x_(x){}

    void print(){
        std::cout << "The current value is: " << x_ << std::endl;
        ++x_;
    }

private:
    int x_;
};

int main(){
    unique_ptr<Example> ptr = make_unique<Example>(5);
    ptr->print();

    unique_ptr<Example> ptr2 = std::move(ptr);
    ptr2->print();
}