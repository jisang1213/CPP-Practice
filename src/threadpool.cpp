#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>
#include <print>

class ThreadPool{
public:
    // Constructor
    ThreadPool(size_t num_threads) : stop_(false){
        for(size_t i=0; i<num_threads; ++i){
            threads_.emplace_back([this](){
                for(;;){
                    std::unique_lock<std::mutex> lock{mtx_};
                    // Wait until the thread is stopped or there is a task in the queue
                    cv_.wait(lock, [this](){ return stop_ || !tasks_.empty(); });
                    if(stop_ && tasks_.empty()) return;
                    // Otherwise pop task from queue and execute
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
        stop_ = true;
        cv_.notify_all();

        // Join all threads
        for(auto& t : threads_){
            if(t.joinable()){
                t.join();
            }
        }
    }

    template <typename F>
    void queueTask(F&& f){
        std::lock_guard<std::mutex> lock(mtx_);
        tasks_.push(std::forward<F>(f));
        cv_.notify_one();
    }

private:
    std::atomic<bool> stop_;
    std::mutex mtx_;
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;
    std::condition_variable cv_;
};

static std::mutex cout_mtx;

int main(){
    auto counter = [](int task_id){
        constexpr size_t N = 100;
        for(int i=0; i<N; ++i){
            cout_mtx.lock();
            std::cout << "Task #" << task_id << " : " << i << std::endl;
            cout_mtx.unlock();
        }
        cout_mtx.lock();
        std::cout << "Task #" << task_id << " is complete" << std::endl;
        cout_mtx.unlock();
    };

    ThreadPool pool(3);
    for(int i=0; i<6; ++i){
        pool.queueTask(std::bind(counter, i));
    }
}