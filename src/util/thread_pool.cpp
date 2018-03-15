// File Name: thread_pool.cpp
// Author: lei
// Created Time: 2018-03-13 20:13:45

#include "thread_pool.h"

namespace nanorpc {
namespace net {

ThreadPool::ThreadPool(size_t threads) 
    :  size_(threads), stop_(false) {
    for (size_t i = 0; i < threads; i++) {
        workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex_);
                    this->condition_.wait(lock, [this]{ return (this->stop_ || this->tasks_.empty()); });
                    if (this->stop_ && this->tasks_.empty()) { 
                        return; 
                    }
                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }
                task();
            }
        }); // end of workers_.emplace_back(...)
    }
}

ThreadPool::~ThreadPool() {
    stop_ = true;
    condition_.notify_all();
    for (auto &w : workers_) { 
        w.join(); 
    }
}

}
}
