#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <set>

/* This file demontrates STL containers
- vector
- deque
- queue
- stack
- map
*/

int main(){
    // Vectors
    std::vector vector = {1,2,3,4};

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

    //Unordered Set
    
}