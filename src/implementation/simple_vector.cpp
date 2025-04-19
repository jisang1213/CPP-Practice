#include <iostream>
#include <stdexcept>

/*
This is an implementation of a simple but inefficient vector
*/
template<typename T>
class Vector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void resize(){
        capacity_ = (capacity_==0) ? 1 : capacity_ * 2; // double the capacity
        T* newdata = new T[capacity_]; // new array
        for(size_t i=0; i<size_; i++){
            newdata[i] = std::move(data[i]);
        }
        delete[] data;
        data = newdata;
    }

    void downsize(){
        capacity_ = capacity_/2;
        T* newdata = new T[capacity_];
        for(size_t i=0; i<size_; i++){
            newdata[i] = std::move(data[i]);
        }
        delete[] data;
        data = newdata;
    }
    
public:
    // Constructor
    Vector() : data(nullptr), size_(0), capacity_(0) {}
    // Destructor
    ~Vector(){
        delete[] data;
    }
    // Copy constructor
    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        data = new T[other.capacity_];
        for(size_t i=0; i < size_; i++){
            data[i] = other.data[i];
        }
    }
    // Move constructor
    Vector(Vector&& other) noexcept : data(other.data), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data = nullptr;
    }
    // Copy assignment operator
    Vector& operator=(const Vector& other){
        // check for self-assignment
        if(this == &other) return *this;
        delete[] data; // delete previous data
        size_ = other.size_;
        capacity_ = other.capacity_;
        data = new T[capacity_];
        // Copy the data
        for(size_t i=0; i < size_; i++){
            data[i] = other.data[i];
        }
        return *this;
    }
    // Move assignemnt operator
    Vector& operator=(Vector&& other) noexcept{
        if(this == &other) return *this;
        delete[] data; // delete previous data
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }
    // Access element at index
    T& operator[](size_t idx){
        return data[idx];
    }
    // Access element with bounds checking
    T& at(size_t idx){
        if(idx >= size_){
            throw std::out_of_range("Index is out of range");
        }
        return data[idx];
    }
    void push_back(const T& value){
        if(size_ == capacity_) resize();
        data[size_++] = value;
    }
    void pop_back(){
        if(size_ == 0){
            throw std::out_of_range("No elements to pop");
        }
        size_--;
        // Half the vector if the size is less than quarter of the capacity
        if(size_ < capacity_/4) downsize();
    }
    T& back(){
        if(size_==0){
            throw std::out_of_range("Vector is empty");
        }
        return data[size_ - 1];
    }
    size_t size(){
        return size_;
    }
    size_t capacity(){
        return capacity_;
    }
    bool empty(){
        return size_ == 0;
    }
    void clear(){
        delete[] data;
        size_ = 0;
        capacity_ = 0;
    }
    void print(){
        for(size_t i = 0; i < size_; i++){
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main(){
    Vector<int> myvector;

    for(size_t i=0; i < 10; i++){
        myvector.push_back(i);
    }
    myvector.print();
    std::cout << "Size is: " << myvector.size() << " and capacity is: " << myvector.capacity() << "\n";
    
    for(size_t i=0; i < 10; i++){
        myvector.pop_back();
    }
    myvector.print();
    std::cout << "Size is: " << myvector.size() << " and capacity is: " << myvector.capacity() << "\n";
}