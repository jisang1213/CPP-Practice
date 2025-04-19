/*
This is an example of a memory efficient vector
*/

#include <new> // placement new
#include <utility> // std::exchange, std::move, std::forward
#include <memory>
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <stdexcept> // std::out_of_range exception
#include <cassert>

template <typename T, typename Alloc = std::allocator<T>>
class Vector{
    using Traits = std::allocator_traits<Alloc>;

public:
    // types (these must exist in accordance with the CPP standard)
    using value_type = T;
    using allocator_type = Alloc;
    
    // Default constructor
    Vector() noexcept : Vector{Alloc()} {}

    // Allocator-accepting ctor
    explicit Vector(const Alloc& alloc) noexcept 
    : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {}

    // Reserve but don't construct
    explicit Vector(size_t n, const Alloc& alloc = Alloc())
    : alloc_(alloc), data_(Traits::allocate(alloc_, n)), size_(0), capacity_(n) {}

    // Use placement new to copy construct n elements
    explicit Vector(size_t n, const T& val, const Alloc& alloc = Alloc())
    : Vector(n, alloc) {
        size_ = n;
        for(size_t i=0; i<size_; i++){
            Traits::construct(alloc_, data_+i, val);
            // new(data_+i) T(val); // placement new
        }
    }

    // Initialize using initialzer list
    Vector(std::initializer_list<T> list, const Alloc& alloc = Alloc())
    : Vector(alloc) {
        for(const T& v: list){
            push_back(v);
        }
    }
    // Copy constructor
    Vector(const Vector& other) 
    : Vector(other.size_, other.alloc_) {
        size_ = other.size_;
        for(size_t i=0; i<size_; ++i){
            Traits::construct(alloc_, data_+i, other.data_[i]);
            // new(data_+i) T(other.data_[i]);
        }
    }
    // Move constructor
    Vector(Vector&& other) noexcept 
    :   alloc_(std::move(other.alloc_)),
        data_(std::exchange(other.data_, nullptr)), 
        size_(std::exchange(other.size_, 0)),
        capacity_(std::exchange(other.capacity_, 0)) {}
    
    friend void swap(Vector& a, Vector& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
        swap(a.capacity_, b.capacity_);
        swap(a.alloc_, b.alloc_);
    }
    // Copy assignment operator 
    Vector& operator=(const Vector& other) {
        if(this==&other) return *this;
        // Copy and swap
        Vector temp(other); // Make copy using copy constructor
        swap(*this, temp);
        return *this;
    }
    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if(this==&other) return *this;
        clear();
        if(data_){
            Traits::deallocate(alloc_, data_, capacity_);
            // ::operator delete(data_);
        }
        using std::exchange;
        size_ = exchange(other.size_, 0);
        capacity_ = exchange(other.capacity_, 0);
        data_ = exchange(other.data_, nullptr);
        return *this;
    }

    ~Vector() noexcept {
        clear();
        if(data_){
            Traits::deallocate(alloc_, data_, capacity_);
            // ::operator delete(data_);
        }
    }
    // Reserve raw memory
    void reserve(size_t n){
        if(n <= capacity_) return;
        T* newdata = Traits::allocate(alloc_, n);
        // T* newdata = allocate(n);
        // Copy the data
        for(size_t i=0; i<size_; ++i){
            Traits::construct(alloc_, newdata + i, std::move(data_[i]));
            Traits::destroy(alloc_, data_+i);
            // new (newdata + i) T(std::move(data_[i]));
            // data_[i].~T(); // Destroy the old object
        }
        // Delete the previous heap block
        if(data_){
            Traits::deallocate(alloc_, data_, capacity_);
        }
        // ::operator delete(data_);
        data_ = newdata;
        capacity_ = n;
    }

    // Function to forward constructor arguments and insert
    template<typename... Args>
    void emplace_back(Args&&... args){
        if(size_>=capacity_){
            reserve(capacity_? capacity_ * 2 : 1);
        }
        Traits::construct(alloc_, data_ + size_, std::forward<Args>(args)...);
        // new (data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }
    
    void push_back(const T& val){ emplace_back(val); }
    void push_back(T&& val){ emplace_back(std::move(val)); }

    void pop_back(){
        if(size_>0){
            --size_;
            Traits::destroy(alloc_, data_+size_);
            // data_[size_].~T();
        }
    }

    // Resize and default construct
    void resize(size_t n){
        if(n < size_){
            for(size_t i=n; i<size_; ++i){
                Traits::destroy(alloc_, data_+i);
                // data_[i].~T();
            }
        }
        reserve(n);
        for (size_t i = size_; i < n; ++i){
            Traits::construct(alloc_, data_ + i);
        }
        size_ = n;
    }
    // Resize and value construct
    void resize(size_t n, const T& val){
        if(n < size_){
            for(size_t i=n; i<size_; ++i){
                Traits::destroy(alloc_, data_+i);
                // data_[i].~T();
            }
        }
        reserve(n);
        // Default construct the new elements
        for(size_t i=size_; i<n; i++){
            Traits::construct(alloc_, data_+i, val);
            // new(data_ + i) T(val);
        }
        size_ = n;
    }

    void shrink_to_fit(){
        if(size_==0){
            Traits::deallocate(alloc_, data_, capacity_);
            // ::operator delete(data_);
            data_ = nullptr;
            capacity_=0;
        }
        else{
            T* newdata = Traits::allocate(alloc_, size_);
            // T* newdata = allocate(size_);
            // Copy the data
            for(size_t i=0; i<size_; ++i){
                Traits::construct(alloc_, newdata + i, std::move(data_[i]));
                Traits::destroy(alloc_, data_ + i);
                // new (newdata + i) T(std::move(data_[i]));
                // data_[i].~T();
            }
            Traits::deallocate(alloc_, data_, capacity_);
            // ::operator delete(data_);
            data_ = newdata;
            capacity_ = size_;
        }
    }

    // Clear the vector, keep the capacity
    void clear() noexcept {
        for(size_t i=0; i<size_; i++){
            Traits::destroy(alloc_, data_+i);
            // data_[i].~T();
        }
        size_ = 0;
    }

    // Accessors
    T& front() {
        if(empty()) throw std::logic_error("Vector is empty");
        return data_[0]; 
    }
    const T& front() const {
        if(empty()) throw std::logic_error("Vector is empty");
        return data_[0];
    }
    T& back() {
        if(empty()) throw std::logic_error("Vector is empty");
        return data_[size_-1];
    }
    const T& back() const {
        if(empty()) throw std::logic_error("Vector is empty");
        return data_[size_-1];
    }

    T& operator[](size_t i){ return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    // Bounds-checked accessors
    T& at(size_t i){
        if(i>=size_) throw std::out_of_range("Index out of range");
        return data_[i];
    }
    const T& at(size_t i) const {
        if(i>=size_) throw std::out_of_range("Index out of range");
        return data_[i];
    }

    // Mutable iterators
    T* begin() { return data_; }
    T* end(){ return data_ + size_; }
    // Const iterators
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
    // Read only iterators
    const T* cbegin() const { return data_; }
    const T* cend() const { return data_ + size_; }

    size_t capacity() const noexcept { return capacity_; }
    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0;}
    
    allocator_type get_allocator() const noexcept { return alloc_; }

private:
    // Function to heap allocate raw memory for n instances of T
    // static T* allocate(size_t n){
    //     return static_cast<T*>(::operator new(n * sizeof(T)));
    // }

    Alloc alloc_;
    T* data_;
    size_t size_, capacity_;
};

void test_default_ctor() {
    Vector<int> v;
    assert(v.empty());
    assert(v.size() == 0);
    assert(v.capacity() == 0);
}

void test_push_pop() {
    Vector<int> v;
    v.push_back(10);
    assert(!v.empty());
    assert(v.size() == 1);
    assert(v.front() == 10 && v.back() == 10);

    v.push_back(20);
    assert(v.size() == 2);
    assert(v[1] == 20);

    v.pop_back();
    assert(v.size() == 1);
    assert(v.back() == 10);

    v.pop_back();
    assert(v.empty());
}

void test_reserve_resize() {
    Vector<int> v;
    v.reserve(5);
    assert(v.capacity() >= 5);
    assert(v.size() == 0);

    v.resize(3);
    assert(v.size() == 3);
    // default‑constructed ints should be 0
    for (size_t i = 0; i < 3; ++i) assert(v[i] == 0);

    v.resize(6, 7);
    assert(v.size() == 6);
    for (size_t i = 0; i < 3; ++i) assert(v[i] == 0);
    for (size_t i = 3; i < 6; ++i) assert(v[i] == 7);

    v.resize(2);
    assert(v.size() == 2);
}

void test_initializer_list() {
    Vector<std::string> v{"a","bb","ccc"};
    assert(v.size() == 3);
    assert(v[0] == "a" && v[1] == "bb" && v[2] == "ccc");
}

void test_copy_move() {
    Vector<int> a{1,2,3,4};
    Vector<int> b = a;      // copy
    assert(b.size() == a.size());
    for (size_t i = 0; i < a.size(); ++i) assert(b[i] == a[i]);

    Vector<int> c = std::move(a);  // move
    assert(c.size() == 4);
    // `a` is now empty
    assert(a.size() == 0 || a.empty());
}

void test_swap() {
    Vector<int> x{1,2}, y{3,4,5};
    swap(x,y);
    assert(x.size()==3 && x[0]==3 && x.back()==5);
    assert(y.size()==2 && y[0]==1 && y.back()==2);
}

void test_at_exception() {
    Vector<int> v{1,2,3};
    bool thrown = false;
    try {
        int x = v.at(5);
        (void)x;
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown);
}

int main() {
    test_default_ctor();
    test_push_pop();
    test_reserve_resize();
    test_initializer_list();
    test_copy_move();
    test_swap();
    test_at_exception();

    std::cout << "All Vector<> tests passed!\n";
    return 0;
}