#include <iostream>

// C-style casts
double a = 3.14;
int b = (int)a;
//or
int c = int(a);

// static casts are used for compatible types
double x = 3.14;
int y = static_cast<int>(x);  // Converts double to int (truncates decimal part)

class Base { virtual void dummy() {} };
class Derived : public Base {};

int main(){
    // Dynamics casts are used when dealing with polymorphism
    // Cast is checked for validity at run time
    // It is used to safely downcast from a base class pointer to a derived class pointer
    Base* b = new Derived();
    Derived* d = dynamic_cast<Derived*>(b);  // Safe cast within the hierarchy

    if (d) {
        std::cout << "Successful cast!" << std::endl;
    } else {
        std::cout << "Failed cast." << std::endl;
    }
}