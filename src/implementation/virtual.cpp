#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<memory>
#include<stdexcept>

using namespace std;
// Virtual shape class
class Shape{
public:
    enum class Type : uint8_t{
        Rectangle=0,
        Square,
        Circle,
        Triangle
    };

    explicit Shape(std::string name, Type type) : name_(std::move(name)), type_(type) {
        cout << "Shape constructor called for " << name << endl;
    }
    virtual ~Shape() = default;
    [[nodiscard]] virtual double getArea() const = 0; // Pure virtual function to be implemented
    [[nodiscard]] std::string getName() const {
        return name_;
    }
    [[nodiscard]] Type getType() const {
        return type_;
    }

protected:
    template<typename... Args>
    void checkDimensions(Args... args){
        if(!((args>0.0) && ...)){
            throw std::invalid_argument("Dimensions must be positive");
        }
    }

private:
    std::string name_;
    Type type_;
};

// Rectangle class
class Rectangle : public Shape {
public:
    Rectangle(double length, double width) : Shape("Rectangle", Type::Rectangle), length_(length), width_(width) {
        checkDimensions(length, width);
    }
    ~Rectangle() override = default;

    [[nodiscard]] double getArea() const override {
        return length_ * width_;
    }

protected:
    Rectangle(std::string name, Type type, double length, double width) : Shape(std::move(name), type), length_(length), width_(width) {
        checkDimensions(length, width);
    }


private:
    double length_, width_;
};

// Square class
class Square : public Rectangle {
public:
    Square(double side) : Rectangle("Square", Shape::Type::Square, side, side) {}
    ~Square() override = default;
};

// Circle class
class Circle : public Shape {
public:
    Circle(double radius) : Shape("Circle", Shape::Type::Circle), radius_(radius){
        checkDimensions(radius);
    }

    ~Circle() override = default;

    [[nodiscard]] double getArea() const override {
        return M_PI * radius_ * radius_;
    }

private:
    double radius_;
};

// Triangle class
class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : Shape("Triangle", Shape::Type::Triangle), a_(a), b_(b), c_(c) {
        checkDimensions(a, b, c);
        // Check for triangle inequality
        if (!((a_ + b_ > c_) && (a_ + c_ > b_) && (b_ + c_ > a_))) {
            throw std::invalid_argument("Triangle side lengths violate inequality (a+b>c, etc.).");
        }
    }

    [[nodiscard]] double getArea() const override {
        double s = 0.5 * (a_ + b_ + c_);
        return std::sqrt(s*(s-a_)*(s-b_)*(s-c_));
    }

private:
    double a_, b_, c_;
};

int main(){
    constexpr size_t numshapes = 4;
    vector<unique_ptr<Shape>> shape_vec;
    shape_vec.reserve(numshapes);

    try{
        shape_vec.push_back(make_unique<Rectangle>(5.0, 6.0));
        shape_vec.push_back(make_unique<Square>(4.0));
        shape_vec.push_back(make_unique<Circle>(3.0));
        shape_vec.push_back(make_unique<Triangle>(3.0, 3.0, 3.0));
        
        shape_vec.push_back(make_unique<Circle>(-1.0)); // This will throw
    }
    catch(const std::invalid_argument& e){
        std::cerr << e.what() << endl;
    }

    for(const auto& shape_ptr : shape_vec){
        cout << "Name is: " << shape_ptr->getName() << '\n';
        cout << "Area of shape is: " << shape_ptr->getArea() << '\n';
        switch(shape_ptr->getType()){
            case Shape::Type::Circle:
                cout << "Type is circle" << endl;
                break;
            case Shape::Type::Rectangle:
                cout << "Type is rectangle" << endl;
                break;
            case Shape::Type::Square:
                cout << "Type is square" << endl;
                break;
            case Shape::Type::Triangle:
                cout << "Type is triangle" << endl;
                break;
        }
        cout << '\n';
    }
}