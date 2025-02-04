#include <iostream>

// This file demonstrates more advanced concepts in classes in C++ like virtual functions and inheritance
// See classes1.cpp for basic class concepts

/*
Topics covered in this file:
- Virtual functions and overriding
- Final keyword to prevent further overriding
- Virtual destructors for proper deallocation of memory
- Virtual inheritance to solve the diamond problem (done in the classes.cpp file)
- Pure virtual functions, abstract classes


Why use virtual functions?

Virtual functions enable Dynamic Dispatch (Runtime Polymorphism) in C++.
Without virtual functions, C++ uses static binding (compile-time function calls).
With virtual functions, dynamic binding (runtime function calls) ensures that the correct 
function is executed even if the object is accessed through a base class pointer or reference.
*/

// 1. Virtual functions and overriding
class Base_virtual{
public:
    virtual void print(){
        std::cout << "This is the base class" << std::endl;
    }
    // Virtual destructor to ensure proper cleanup of derived objects when deleting via base pointer
    virtual ~Base_virtual(){
        std::cout << "Base_virtual destructor called." << std::endl;
    }
};
class Derived_virtual: public Base_virtual{
public:
    Derived_virtual() : data_(new int(5)) {}
    // Override keyword is optional but helps to avoid mistakes
    void print() override{
        std::cout << "This is the derived class" << std::endl;
    }
    // Destructor to release resources
    ~Derived_virtual(){
        std::cout << "Derived_virtual destructor called." << std::endl;
        delete data_; // This will not be called using the base pointer if the base class destructor is not virtual
    }

private:
    int *data_; // Pointer to some dynamically allocated data
};

// 2. Virtual inheritance (to solve the diamond problem) and final keyword
// diamond inheritance problem arises when a derived class inherits from two classes that have a common base class
class Person {
public:
    // Three explicit constructors for Person
    explicit Person(std::string name = "unknown", int age = -1) : name_(name), age_(age){}
    explicit Person(int age) : name_("unknown"), age_(age){}
    // Friend class declaration allows Dog class to access private and protected members of Person class
    friend class Dog;
    /*
    Always declare a virtual destructor to ensure the derived class destructors are called when 
    deleting a derived class instance through the Base pointer
    */
    virtual ~Person(){}

    virtual std::string getinfo(){
        return name_ + ", " + std::to_string(age_);
    }
// These members are only accessible from inside the Person class
private:
    std::string name_;
    int age_;
};

class Student : virtual public Person {
public:
    explicit Student(std::string name, int age, int studentID) 
    : Person(name, age), studentID_(studentID){}

    std::string getinfo() override {
        return Person::getinfo() + ", " + std::to_string(studentID_);
    }
// Protected members are accessible from derived classes (StudentAthlete)
protected:
    int studentID_;
};

class Athlete : virtual public Person {
public:
    explicit Athlete(std::string name, int age, std::string sport)
    : Person(name, age), sport_(sport){}

    std::string getinfo() override{
        return Person::getinfo() + ", " + sport_;
    }
// Protected members are accessible from derived classes (StudentAthlete)
protected:
    std::string sport_;
};

// One instance of the base class is created when the 'StudentAthlete' class is created
class StudentAthlete final: public Student, public Athlete {
public:
    // All three constructors should be called explicitly
    explicit StudentAthlete(std::string name, int age, int ID, std::string sport)
    : Person(name, age), Athlete(name, age, sport), Student(name, age, ID){}

    // This needed to be overriden to avoid ambiguity. The final keyword prevents this function from
    // being further overriden in derived classes (applies only to virtual functions)
    std::string getinfo() override final {
        return Person::getinfo() + ", " + std::to_string(studentID_) + ", " + sport_;
    }
};

// The 'final' keyword prevents another class inheriting from the Dog class
class Dog final{
public:
    explicit Dog(Person* owner, std::string name = "unknown") : owner_(owner), name_(name){}
    
    std::string getinfo(){
        return "My name is " + name_ + " and my owner is " + owner_->name_;
    }
private:
    std::string name_;
    Person* owner_;
};

// 3. A pure virtual class(or abtract class) in C++ is a class that has at least one pure virtual function (no implementation)
class Shape {
public:
    // Pure virtual function
    virtual void draw() const = 0;

    // Optional: Virtual destructor to allow proper cleanup of derived objects
    virtual ~Shape() {}
};

// Derived class: Implements Shape interface
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Another derived class: Implements Shape interface
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle" << std::endl;
    }
};


int main(){
    // 1. Virtual functions and overriding
    Base_virtual* base2 = new Derived_virtual();
    base2->print(); // This calls the derived class print() due to virtual dispatch
    delete base2; // Calls the derived class destructor first, then the base class destructor

    // 2. Virtual inheritance and final keyword
    StudentAthlete s1("John", 19, 20190837, "baseball");
    std::cout << s1.getinfo() << std::endl;
    Dog d1(&s1, "Puff");
    std::cout << d1.getinfo() << std::endl;

    // 3. Pure virtual functions and abstract classes
    // Shape s;  // Error: Cannot instantiate an abstract class
    Shape* shape1 = new Circle();   // OK: Using polymorphism
    Shape* shape2 = new Rectangle(); 
    shape1->draw();  // Calls Circle::draw()
    shape2->draw();  // Calls Rectangle::draw()
    delete shape1;
    delete shape2;
}