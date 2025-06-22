#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <chrono>
#include <atomic>
#include <condition_variable> 

/*
This file demonstates the use of mutexes and condition variables through the implementation of a thread pool
*/

class ThreadPool{
public:
    // Constructor
    ThreadPool(size_t num_threads) : stop(false) {
        // Create a vector of threads for handling the tasks
        for(size_t i=0; i<num_threads; ++i){
            threads_.emplace_back([this](){
                for(;;){
                    // Get a task from the queue
                    std::unique_lock<std::mutex> lock(mtx_);
                    // Wait until the thread is stopped or there is a task in the queue
                    cv.wait(lock, [this](){ return stop || !tasks_.empty(); }); 
                    /*
                    The wait() call will check the predicate and return immedietely if true. Otherwise, it will release the mutex
                    and wait for a signal to be waken up (signal may be missed if sent before waiting). Upon waking up, it will check the 
                    predicate and return if true. Otherwise, it will go back into wait state.
                    The above is functionally equivalent to:

                    while(!condition){
                        cv.wait(lock);
                    }
                    */

                   if(stop && tasks_.empty())
                        return;
                    auto task = std::move(tasks_.front());
                    tasks_.pop();
                    lock.unlock();
                    // Execute the task
                    task();
                }
            });
        }
    }
    // Destructor
    ~ThreadPool(){
        stop = true;
        cv.notify_all();
        // Join all threads
        for(auto& t : threads_){
            if(t.joinable()){
                t.join();
            }
        }
    }

    // Function to add task to queue
    template <typename F>
    void queueTask(F&& f){
        std::lock_guard<std::mutex> lock(mtx_);
        tasks_.push(std::forward<F>(f));
        cv.notify_one();
    }
    
private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mtx_;
    std::atomic<bool> stop;
    std::condition_variable cv;
};

static std::mutex cout_mtx;

int main() {
    constexpr size_t num_threads = 5;
    // Create a threadpool
    ThreadPool pool(num_threads);
    std::cout << "Thread pool created with " << num_threads << " threads\n";

    // Add 5 tasks to the task queue
    for(int i=0; i<20; ++i){
        pool.queueTask([i](){
            cout_mtx.lock();
            std::cout << std::this_thread::get_id() << " is executing task " << i << "\n";
            cout_mtx.unlock();
            // Simulate some work
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }
}
