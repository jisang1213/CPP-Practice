#include <iostream>
#include <cstring>

/*
Rule of zero, three, five are important concepts when creating classes in C++

There are two different types of value: L values and R values

*/

class String {
private:
    char* data; // Pointer to hold the string data

public:
    // Constructor
    String(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Copy Constructor
    String(const String& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Copy Assignment Operator
    String& operator=(const String& other) {
        if (this == &other) return *this; // Handle self-assignment
        delete[] data; // Free existing resource
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        return *this;
    }

    // Move Constructor
    String(String&& other) noexcept : data(other.data) {
        other.data = nullptr; // Leave the other object in a valid state
    }

    // Move Assignment Operator
    String& operator=(String&& other) noexcept {
        if (this == &other) return *this; // Handle self-assignment
        delete[] data; // Free existing resource
        data = other.data; // Transfer ownership
        other.data = nullptr; // Leave the other object in a valid state
        return *this;
    }

    // Function to display the string
    void display() const {
        std::cout << data << std::endl;
    }
};

int main() {
    String str1("Hello, World!");
    String str2 = str1; // Calls Copy Constructor
    str2.display();

    String str3;
    str3 = str1; // Calls Copy Assignment Operator
    str3.display();

    String str4 = std::move(str1); // Calls Move Constructor
    str4.display();

    String str5;
    str5 = std::move(str2); // Calls Move Assignment Operator
    str5.display();

    return 0;
}
