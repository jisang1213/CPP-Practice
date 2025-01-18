#include <iostream>
#include <string>

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

    // Custom shared_ptr
    template <typename T>
    class shared_ptr{
    private:
        // Control block to store the pointer and reference counts
        struct ControlBlock{
            T* ptr;     // Pointer to the resource
            int ref_count; // Strong reference count
            int weak_count; // Weak reference count
            
            ControlBlock(T* p) : ptr(p), ref_count(1), weak_count(0) {}
            ~ControlBlock() { delete ptr; }
        };

        ControlBlock* control_block;

    public:
        // Contructor
        explicit shared_ptr(T* p = nullptr) : control_block(p ? new ControlBlock(p) : nullptr) {}

        // Destructor
        ~shared_ptr() {
            if(control_block && --control_block->ref_count==0){
                delete control_block;
            }
        }

        // Copy constructor
        shared_ptr(const shared_ptr& other) noexcept : control_block(other.control_block) {
            if (control_block){
                ++control_block->ref_count;
            }
        }

        // Copy assignment operator
        shared_ptr& operator=(const shared_ptr& other) noexcept {
            if(this != &other){
                if(control_block && --control_block->ref_count==0){
                    delete control_block;
                }
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
                if(control_block && --control_block->ref_count==0){
                    delete control_block;
                }
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
        T* get(){
            return control_block ? control_block->ptr : nullptr;
        }

        // Reset shared pointer
        void reset(T* new_ptr = nullptr){
            if(control_block && --control_block->ref_count==0){
                delete control_block;
            }
            control_block = new_ptr ? new ControlBlock(new_ptr) : nullptr;
        }

        // Get reference count
        int use_count(){
            return control_block ? control_block->ref_count : 0;
        }

        // Explicit conversion to bool
        explicit operator bool() const {
            return control_block && control_block->ptr;
        }

    };

}

