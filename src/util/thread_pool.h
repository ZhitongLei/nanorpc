//Copyright (c) 2012 Jakob Progsch, Václav Zeman
//
//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.
//
//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.

#ifndef __UTIL_THREAD_POOL_H__
#define __UTIL_THREAD_POOL_H__

#include <atomic>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace nanorpc {
namespace net {

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ~ThreadPool();

    size_t Size() const { return size_; }

    template<typename F, typename... Args>
    auto Enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;
    size_t size_;
    
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::atomic<bool> stop_;
};


template<typename F, typename... Args>
auto ThreadPool::Enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared< std::packaged_task<return_type()> >(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        if (stop_) {
            throw std::runtime_error("Enqueue on stopped ThreadPool");
        }
        tasks_.emplace([task]() { (*task)(); });
    }
    condition_.notify_one();
    return res;
}

}
}

#endif
