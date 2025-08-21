#include <iostream>
#include <future>
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <chrono>

using namespace std::chrono_literals;

// Basic use of std::async to asynchronously do some task
int calculate_sum(const std::vector<int>& vec, int start, int end){
    return std::accumulate(vec.begin() + start, vec.begin() + end, 0);
}

// std::future and std::promise for sending values between threads
void set_answer_on_promise(std::promise<int>&& promise, int a, int b){
    std::cout << "Worker thread is computing value..." << std::endl;
    std::this_thread::sleep_for(1s);
    try{
        int result = a+b;
        promise.set_value(result);
    }
    catch(...){
        promise.set_exception(std::current_exception());
    }
}

int main(){
    constexpr int n = 10000;
    int mid = n / 2;
    std::vector<int> vec(n);
    std::iota(vec.begin(), vec.end(), 1);
    // std::async makes copy by default even though the function argument is const &. Must use std::cref to pass by reference
    std::future<int> f = std::async(std::launch::async, std::cref(calculate_sum), vec, mid, n);
    
    int first_half = std::accumulate(vec.begin(), vec.begin() + mid, 0);
    int second_half = f.get();
    int sum = first_half + second_half;
    int expected = n * (n+1) / 2;

    using namespace std;
    if(sum==expected){
        cout << "Got expected result: " << sum << endl;
    }
    else{
        cout << "Wrong result" << endl;
    }

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    // Launch worker thread
    std::thread t(set_answer_on_promise, std::move(promise), 4, 5);

    int result;
    try{
        result = future.get();
        cout << "Received result from worked thread: " << result << endl;
    }
    catch(const std::exception& e){
        cerr << "Caught exception from worker thread: " << e.what() << endl;
    }
    t.join();
}

