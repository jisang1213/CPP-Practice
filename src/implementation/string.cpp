#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstddef>
#include<utility>

namespace JS{
class String{
private:
    char* data_;
    size_t length_;
    
    void allocate_and_copy(const char* source, size_t len){
        // Allocate enough space for len+1
        data_ = new char[len+1];
        length_ = len;
        if(length_>0){
            std::memcpy(data_, source, len);
        }
        data_[length_] = '\0'; // Null terminator
    }

public:
    // Default constructor for creating an empty string
    String() : data_(new char[1]), length_(0) {
        data_[0] = '\0';
    }
    // Construct from char string
    String(const char* c_str){
        length_ = c_str ? std::strlen(c_str) : 0;
        allocate_and_copy(c_str, length_);
    }
    // Construct for a specific length of a single character
    String(size_t count, char c){
        data_ = new char[count+1];
        std::memset(data_, c, count);
        data_[count] = '\0';
        length_ = count;
    }
    // Copy constructor
    String(const String& other){
        allocate_and_copy(other.data_, other.length_);
    }
    // Move constructor
    String(String&& other) noexcept {
        data_ = std::exchange(other.data_, nullptr);
        length_ = std::exchange(other.length_, 0);
    }
    // Copy assignment operator
    String& operator=(const String& other){
        if(this != &other){
            // Create a temporary
            String temp(other);
            std::swap(data_, temp.data_);
            std::swap(length_, temp.length_);
            // When temp goes out of scope, it deletes the old data
        }
        return *this;
    }
    // Move assignment operator
    String& operator=(String&& other) noexcept {
        if(this != &other){
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            length_ = std::exchange(other.length_, 0);
        }
        return *this;
    }
    // Assignment from C-string
    String& operator=(const char* c_str){
        delete[] data_;
        String temp(c_str);
        std::swap(data_, temp.data_);
        std::swap(length_, temp.length_);
        return *this;
    }
    // Destructor
    ~String(){
        delete[] data_;
    }
    
    char& operator[](size_t index){
        return data_[index];
    }
    const char& operator[](size_t index) const {
        return data_[index];
    }

    char& at(size_t index){
        if(index < length_){
            return data_[index];
        }
        else{
            throw std::out_of_range("index is out of range");
        }
    }
    const char& at(size_t index) const {
        if(index < length_){
            return data_[index];
        }
        else{
            throw std::out_of_range("index is out of range");
        }
    }
    // Getters
    size_t length() const noexcept {
        return length_;
    }
    size_t size() const noexcept {
        return length_;
    }
    bool empty() const noexcept {
        return length_ == 0;
    }
    // Get the underlying C-style string
    const char* c_str() const noexcept {
        return data_;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s);

    // Three-way comparison operator
    auto operator<=>(const String& other) const {
        return std::strcmp(data_, other.data_) <=> 0;
    }

    bool operator==(const String& other) const {
        if(length_ != other.length_) return false;
        if(length_ == 0) return true;
        return std::strcmp(data_, other.data_) == 0;
    }
};

std::ostream& operator<<(std::ostream& os, const String& s){
    os << s.c_str();
    return os;
}
}

using namespace std;

int main(){
    JS::String a("This is an example string");
    cout << a << endl;

    JS::String s1 = "abc";
    JS::String s2 = "def";

    cout << boolalpha;
    cout << "abc comes before def? " << (s1 < s2 ? true : false) << endl;
}