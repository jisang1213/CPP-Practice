#include "custom.hpp"
#include <utility> // For std::move


class Person{
private:
    std::string name_;

public:
    explicit Person(std::string name) : name_(name) {}
    void sayname(){
        std::cout << "Name is: " << name_ << std::endl;
    }
};

int main(){

    Custom::unique_ptr<Person> p1(new Person("Joe"));
    p1->sayname();

    Custom::unique_ptr<Person> p2 = std::move(p1);
    p2->sayname();

    if(!p1.get()){
        std::cout << "p1 is a nullptr" << std::endl;
    }

    Custom::shared_ptr<Person> p3;
    {
        Custom::shared_ptr<Person> p4(new Person("Bob"));
        p4->sayname();
        std::cout << "Reference count of Bob: " << p4.use_count() << std::endl;
        p3 = p4; // share ownership of the object, reference counts increases to 2
        std::cout << "Reference count of Bob: " << p3.use_count() << std::endl;
    }
    // p4 goes out of scope so reference count falls back to 1
    std::cout << "Reference count of Bob: " << p3.use_count() << std::endl;
    
    p3.reset();
    // Reference count drops to 0 after reset
    std::cout << "Reference count of Bob: " << p3.use_count() << std::endl;

    // Now, uncomment the following will result in nullptr access error
    // p3->sayname();

    return 0;    
}