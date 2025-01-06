#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

/* This file demontrates STL iterators*/
// We will implement an iterator for a custom dynamic array

template<typename T>
class DynamicArray{
public:
    // Constructor and destructor
    DynamicArray(size_t size) : size_(size), data_(new T[size]) {}
    ~DynamicArray(){delete[] data_;}

    // Access elements
    T& operator[](size_t index){return data_[index];}
    const T& operator[](size_t index) const {return data_[index];}
    size_t size() const {return size_;}

    // Nested iterator class
    class Iterator{
    public:
        Iterator(T* ptr) : ptr_(ptr) {}

        // Overload the * operator
        T& operator*() const { return *ptr_;}

        // Overload the ++ operator for advancing
        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        // Overload the == operator for comparison
        bool operator==(const Iterator& other){return ptr_ == other.ptr_;}
        // Overload the != operator for comaparison
        bool operator!=(const Iterator& other){return ptr_ != other.ptr_;}
    private:
        T* ptr_;
    };

    Iterator begin(){return Iterator(data_);}
    Iterator end(){return Iterator(data_ + size_);}

private:
    T* data_;
    size_t size_;
};

int main(){
    DynamicArray<int> arr(5);
    // Fill the array:
    for(size_t i=0; i<arr.size(); i++){
        arr[i] = static_cast<int>(i*10);
    }

    // Use the custom iterator to print out the entire vector:
    for(auto it = arr.begin(); it != arr.end(); ++it){
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}