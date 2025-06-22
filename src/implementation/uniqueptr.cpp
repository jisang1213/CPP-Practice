#include <iostream>
#include <utility>

namespace JS{
    template<typename T>
    class unique_ptr{
    public:
        // Default constructors
        unique_ptr() : ptr_(nullptr){}
        // Constructor
        unique_ptr(T* ptr) : ptr_(ptr){}
        // Destructor
        ~unique_ptr() noexcept {
            delete ptr_;
        }
        // Delete the copy constructor
        unique_ptr(const unique_ptr& other) = delete;
        // Move constructor
        unique_ptr(unique_ptr&& other) noexcept {
            ptr_ = std::exchange(other.ptr_, nullptr);
        }
        // Delete the copy assignment operator
        unique_ptr& operator=(const unique_ptr& other) = delete;
        // Move assingment operator
        unique_ptr& operator=(unique_ptr&& other) noexcept {
            if(this == &other){
                return *this;
            }
            delete ptr_;
            ptr_ = std::exchange(other.ptr_, nullptr);
            return *this;
        }
        // Dereference operator
        T& operator*(){
            return *ptr_;
        }
        // Const dereference operator
        T& operator*() const {
            return *ptr_;
        }
        // Arrow operator
        T* operator->(){
            return ptr_;
        }
        // Const arrow operator
        T* operator->() const {
            return ptr_;
        }
        // Get function 
        T* get() const {
            return ptr_;
        }
        void reset(T* p){
            delete ptr_;
            ptr_ = p;
        }
        void release(){
            delete ptr_;
            ptr_ = nullptr;
        }

    private:
        T* ptr_;
    };
}

using namespace std;

int main(){
    JS::unique_ptr<int> p(new int{5});
    cout << "The integer pointed to by the unique ptr is " << *p << endl;
}