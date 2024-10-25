// In C++, an enum (short for enumeration) is a user-defined data type that consists of 
// a set of named integral constants, making your code more readable and manageable.
#include <iostream>

enum Color {
    Red,    // Automatically assigned value 0
    Green,  // 1
    Blue    // 2
};

// You can also assign custom integral values to enums
enum ErrorCode {
    Success = 0,
    NotFound = 404,
    ServerError = 500
};

// Scoped enums (C++11)
enum class Color_scoped {
    Red,    // by default the first value is 0, second 1, and so on
    Green,
    Blue
};
// without scoped enums, two enums could have conflicting names

// You can also change the underlying type of enums to unsigned char, int, long, etc. but it must be scoped enums
enum class Status : unsigned int {
    OK = 200,
    NotFound = 404,
    ServerError = 500
};

// enums can also have char values:
#include <iostream>

enum class Direction : char { 
    North = 'N', 
    South = 'S', 
    East = 'E', 
    West = 'W' 
};

int main(){
    Color favoriteColor = Green;
    if (favoriteColor == Green) {
        std::cout << "The color is Green!" << std::endl;
    }

    ErrorCode code = ServerError;
    std::cout << "Error code: " << code << std::endl;  // Output: 500
    
    Color_scoped color = Color_scoped::Green;
    if (color == Color_scoped::Green) {
        std::cout << "Color is Green!" << std::endl;
    }

    // Converting enums to ints:
    int color_value = static_cast<int>(Color::Green);
    std::cout << "Color value: " << color_value << std::endl;

    Direction dir = Direction::East;
    switch (dir) {
        case Direction::North: std::cout << "North"; break;
        case Direction::South: std::cout << "South"; break;
        case Direction::East:  std::cout << "East";  break;
        case Direction::West:  std::cout << "West";  break;
    }
    std::cout << std::endl;

    // Or print the underlying value directly:
    char dirChar = static_cast<char>(dir);
    std::cout << "Direction: " << dirChar << std::endl;  // Output: E

    // Printing an unscoped enum works out of the box
    std::cout << "Print value of enum: " << favoriteColor << std::endl;
    // Printing a scoped enum requires a cast
    std::cout << "Print value of enum class after casting: " << static_cast<int>(color) << std::endl;
}
