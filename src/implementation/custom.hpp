#include <iostream>
#include <string>
#include <atomic> // For thread-safe access to reference counters

namespace Custom{
    // Custom unique_ptr
    template <typename T>
    class unique_ptr{
    private:
        T* ptr;

    public:
        explicit unique_ptr(T* p = nullptr) : ptr(p) {}
        ~unique_ptr(){ delete ptr; }

        // Delete the copy constructor and the copy assignment operator
        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        // Move constructor
        unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr){
            other.ptr = nullptr;
        }

        // Move assignment operator
        unique_ptr& operator=(unique_ptr&& other) noexcept{
            if(this != &other){
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        T& operator*() const {
            if(!ptr){
                throw std::runtime_error("Null pointer access");
            }
            return *ptr;
        }
        T* operator->() const { 
            if(!ptr){
                throw std::runtime_error("Null pointer access");
            }
            return ptr;
        }
        T* get() const {
            return ptr;
        }

        T* release() {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }

        void reset(T* newptr = nullptr){
            delete ptr;
            ptr = newptr;
        }
        explicit operator bool() const {
            return ptr != nullptr;
        }
    };

    // Forward declaration of weak_ptr
    template <typename T>
    class weak_ptr;

    // Custom shared_ptr
    template <typename T>
    class shared_ptr{
    private:
        // Control block to store the pointer and reference counts
        struct ControlBlock{
            T* ptr;     // Pointer to the resource
            std::atomic<int> ref_count; // Strong reference count
            std::atomic<int> weak_count; // Weak reference count
            
            ControlBlock(T* p) : ptr(p), ref_count(1), weak_count(0) {}
            ~ControlBlock() { delete ptr; }
        } *control_block; // Pointer to ControlBlock struct

    private:
        void release(){
            if(control_block && --control_block->ref_count==0){
                delete control_block->ptr;
                if(control_block->weak_count==0){
                    delete control_block;
                }
            }
        }

    public:
        // Contructor
        explicit shared_ptr(T* p = nullptr) : control_block(p ? new ControlBlock(p) : nullptr) {}

        // Destructor
        ~shared_ptr() {
            release();
        }

        // Copy constructor
        shared_ptr(const shared_ptr& other) noexcept : control_block(other.control_block) {
            if (control_block){
                ++control_block->ref_count;
            }
        }

        // Copy constructor from weak_ptr
        shared_ptr(const weak_ptr<T>& weak) : control_block(weak.control_block) {
            if(control_block){
                ++control_block->ref_count;
            }
        }

        // Copy assignment operator
        shared_ptr& operator=(const shared_ptr& other) noexcept {
            if(this != &other){
                release(); // Since the current instance is being overwritten
                control_block = other.control_block;
                if(control_block){
                    ++control_block->ref_count;
                }
            }
            return *this;
        }

        // Move constructor
        shared_ptr(shared_ptr&& other) noexcept : control_block(other.control_block){
            other.control_block = nullptr;
        }

        // Move assignment operator
        shared_ptr& operator=(shared_ptr&& other) noexcept {
            if(this != &other){
                release();
                control_block = other.control_block;
                other.control_block = nullptr;
            }
            return *this;
        }

        // Dereference operator
        T& operator*(){
            if(!control_block || !control_block->ptr){
                throw std::runtime_error("Deferencing nullptr");
            }
            return *control_block->ptr;
        }

        // Arrow operator
        T* operator->(){
            if(!control_block || !control_block->ptr){
                throw std::runtime_error("Deferencing nullptr");
            }
            return control_block->ptr;
        }

        // Raw pointer
        T* get() const {
            return control_block ? control_block->ptr : nullptr;
        }

        // Reset shared pointer
        void reset(T* new_ptr = nullptr){
            release();
            control_block = new_ptr ? new ControlBlock(new_ptr) : nullptr;
        }

        // Get reference count
        int use_count() const {
            return control_block ? control_block->ref_count.load() : 0;
        }

        // Explicit conversion to bool
        explicit operator bool() const {
            return control_block && control_block->ptr;
        }

        friend class weak_ptr<T>;
    };

    // Weak pointer (non-owning reference to an object managed by shared pointer)
    template <typename T>
    class weak_ptr{
    private:
        typename shared_ptr<T>::ControlBlock* control_block;

    private:
        void release(){
            if(control_block && --control_block->weak_count==0 && control_block->ref_count==0){
                delete control_block;
            }
        }
    
    public:
        // Contructor
        weak_ptr() : control_block(nullptr) {}

        // Contructor from shared pointer
        weak_ptr(const shared_ptr<T>& shared) : control_block(shared.control_block) {
            if(control_block){
                ++control_block->weak_count;
            }
        }

        // Destructor
        ~weak_ptr(){
            release();
        }

        // Copy constructor
        weak_ptr(const weak_ptr& other) : control_block(other.control_block) {
            if(control_block){
                ++control_block->weak_count;
            }
        }

        // Move constructor
        weak_ptr(weak_ptr&& other) noexcept : control_block(other.control_block) {
            other.control_block = nullptr;
        }

        // Lock: Create a shared_ptr if the resource is still valid
        shared_ptr<T> lock() const {
            if(control_block && control_block->ref_count > 0){
                return shared_ptr<T>(*this);
            }
            return shared_ptr<T>(); // otherwise return an empty shared pointer
        }
    };
}