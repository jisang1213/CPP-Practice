/*
This files shows the use of the new operator, placement new, and allocators
*/

#include <new> // for std::nothrow and placement new
#include <memory>
#include <iostream>

class Example{
public:
    Example() {}
    Example(int a, int b) : a_(a), b_(b) {}
    int getfirst(){ return a_; }
    int getsecond(){ return b_; }

private:
    int a_, b_;
};

int main(int argc, char** argv){
    // Use new to create a single 
    int* a = new int; // Default-initialized. Indeterminate.
    int* b = new int(); // Initialized to 0
    int* c = new int{}; // Initialized to 0
    int* d= new int(5); 
    int* e= new int{5}; 
    
    Example* f = new Example(2,3);
    delete f;

    int* a1 = new int[5];         // five indeterminate ints
    int* a2 = new int[5]();       // all five = 0
    int* a3 = new int[5]{ };      // all five = 0
    int* a4 = new int[5]{1,2,3};  // a4[0]=1, a4[1]=2, a4[2]=3, rest=0

    // By default, new throws std::bad_alloc on failure. To get nullptr instead:
    int* q1 = new (std::nothrow) int;        // indeterminate or nullptr
    int* q2 = new (std::nothrow) int();      // zero or nullptr
    int* q3 = new (std::nothrow) int{};     // zero or nullptr
    int* q4 = new (std::nothrow) int(99);    // 99 or nullptr
    int* q5 = new (std::nothrow) int{99};    // 99 or nullptr

    // Array allocation
    int* p1 = new int[5];         // five indeterminate ints
    int* p2 = new int[5]();       // all five = 0
    int* p3 = new int[5]{};      // all five = 0
    int* p4 = new int[5]{1,2,3};  // a4[0]=1, a4[1]=2, a4[2]=3, rest=0

    int* b1 = new (std::nothrow) int[5];
    int* b2 = new (std::nothrow) int[5]();
    int* b3 = new (std::nothrow) int[5]{1,2,3};

    // Remember to call delete on everything
    delete a1;
    delete a2;
    delete a3;
    delete a4;

    delete q1;
    delete q2;
    delete q3;
    delete q4;
    delete q5;

    delete[] p1;
    delete[] p2;
    delete[] p3;
    delete[] p4;

    delete[] b1;
    delete[] b2;
    delete[] b3;

    // We can also use a std allocator to allocate heap memory

    std::allocator<int> alloc;
    // Allocate raw memory like this:
    int* data = alloc.allocate(10); // allocate for 10 ints
    // Construct objects in-place
    for(size_t i=0; i<10; i++){
        alloc.construct(data+i, int(i*10));
    }


}