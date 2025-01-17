#include <iostream>
#include <string>

/* To Cover:
- Public, private and protected members
- Explicit keyword for disabling implicit conversions
- Initializer list in constructor
- Overloaded constructors
- Operator overloading
- Friend class and functions
- Member variable syntax
- Naming conventions for member variables - postfix _
*/

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

/*
Virtual inheritance ensures that one once instance of the base class is created when the 
StudentAthlete class is created
*/
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

// final keyword prevents another class inheriting from the Dog class
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


int main(){
    StudentAthlete s1("John", 19, 20190837, "baseball");
    std::cout << s1.getinfo() << std::endl;
    Dog d1(&s1, "Puff");
    std::cout << d1.getinfo() << std::endl;
}