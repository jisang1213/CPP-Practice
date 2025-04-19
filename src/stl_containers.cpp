#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>

/*
This file demontrates STL containers
- vector
- deque (double ended queue)
- queue (FIFO)
- stack (LIFO)
- priority queue (max heap)
- map (key value pairs)
- unordered_map (key value pairs in any order)
- set (unique elements)

For O(1) insertion/deletion given iterator, use lists:
- lists (doubly linked list)
- forward_list (singly linked list)
*/

void print(std::vector<int>& vec){
    for (const auto& x : vec){
        std::cout << x << ", ";
    }
    std::cout << std::endl; 
}

int main(){
    // Vectors
    std::vector vec = {1,2,3,4};
    print(vec);
    vec.clear(); // This removes all elements and makes the size to 0. The capacity is unchanged
    std::cout << "The size of the vector is: " << vec.size() << "\n";
    std::cout << "The capacity of the vector is: " << vec.capacity() << "\n";
    vec.shrink_to_fit(); // This shrinks the capacity to the size (compiler may ignore)
    std::cout << "The capacity of the vector is: " << vec.capacity() << "\n";

    // Use of assign to complete replace the contents of a vector
    vec.assign({10,20});
    print(vec);
    vec.assign(5,42); // Replace with 5 copies of 42
    print(vec);
    std::vector source = {1,2,3,4,5,6};
    vec.assign(source.begin(), source.end()); // You can pass the iterators of another vector to copy it
    print(vec);

    // Dequeue (double-ended queue sequence container)
    std::deque<int> dq = {1,2,3};
    // Adding elements
    dq.push_front(0);
    dq.push_back(4);
    // Accesing elements at the ends
    std::cout << "The element at the front is " << dq.front() << "\n";
    std::cout << "The element at the back is " << dq.back() << "\n";
    // Random access O(1)
    std::cout << "The elements at index 3 is " << dq[3] << "\n";
    // Removing elements (doesn't return anything)
    dq.pop_front();
    dq.pop_back();

    // Queue (FIFO container adapter)
    std::queue<int> q;
    for(int i=0; i<3; i++){
        q.push(i);
        std::cout << "Pushed to queue: " << q.back() << "\n";
    }

    while(!q.empty()){
        std::cout << "The elements at the front of the queue is " << q.front() << "\n";
        q.pop();
    }

    // Stack (LIFO container adapter)
    std::stack<int> s;
    for(int i=0; i<3; i++){
        s.push(i);
        std::cout << "Added to stack:" << i << std::endl;
    }
    std::cout << "Size of the stack is: " << s.size() << std::endl;
    while(!s.empty()){
        std::cout << "Top of stack: " << s.top() << std::endl;
        s.pop();
    }

    // Priority Queue (Uses max-heap by default. Uses std::vector by default)
    std::priority_queue<int> pq;
    pq.push(20);
    pq.push(5);
    pq.push(10);
    std::cout << "Size of the priority queue is: " << pq.size() << std::endl;
    while(!pq.empty()){
        std::cout << "Top of priority queue is: " << pq.top() << std::endl;
        pq.pop();
    }

    // Ordered set (Used balanced search tree to maintain unique elements in sorted order)
    std::set<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(20);
    for(int x : set){
        std::cout << x << " ";
    }
    set.erase(10); // returns 1 if elements exists, 0 if not
    std::cout << "\nExists: " << (set.count(10) ? "Yes" : "No") << std::endl; // Output

    // Unordered Set (Uses hashtable)
    std::unordered_set<int> unordered_set;
    unordered_set.insert(10);
    unordered_set.insert(20);
    unordered_set.insert(30);
    // attempt to insert an element already in the set
    unordered_set.insert(30); // this will be a nop
    // Print all elements in the set
    std::cout << "Elements in the unordered set: ";
    for(const auto& x : unordered_set){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    // Check if 20 is in the set:
    if(unordered_set.find(20) != unordered_set.end()){
        std::cout << "20 is in the set" << std::endl;
    }
    unordered_set.erase(20);
    std::cout << "The size of the unordered set is: " << unordered_set.size() << std::endl;

    // Map (sorted key-value pairs)
    std::map<int, std::string> map;
    // Insert elements
    map[0] = "Apple";
    map[1] = "Banana";
    map[2] = "Cherry";
    // Or use insert() with {}
    map.insert({4, "Date"});
    // Or use insert() with std::make_pair();
    map.insert(std::make_pair(5, "Orange"));

    // Accesing the map via a key (without inserting a new value)
    try{
        std::cout << "Value for key 2: " << map.at(2) << "\n"; // exception is thrown if key does not exist
    }
    catch(const std::out_of_range& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Wrong way:
    std::string sample = map[6]; // This will not only access but also insert a default value

    // Check if a key exists in the map - find() returns an iterator to the pair
    auto it = map.find(2);
    if(it != map.end()){
        std::cout << "Key 2 found in the map with value: " << it->second << std::endl;
    }
    else{
        std::cout << "Key 2 not found in the map" << std::endl;
    }

    // Print the key value pairs in the map
    for(const auto& pair : map){
        std::cout << "Key: " << pair.first << " Value: " << pair.second << std::endl;
    }

    // It is better to use structure bindings for clarity
    for(const auto& [key, value] : map){
        std::cout << "Key: " << key << " Value: " << value << std::endl;
    }

    // Erase key value pairs
    map.erase(2); 
    std::cout << "The size of the map is: " << map.size() << std::endl;

    // Unordered map - hashtable version of map. Same API, just no specific order of the keys
}