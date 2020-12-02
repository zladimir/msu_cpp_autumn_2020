#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <future>
#include <functional>

class ThreadPool
{
	std::vector<std::thread> pool_;
	std::condition_variable condition_;
	std::queue<std::function<void()>> tasks_;
	std::atomic<bool> done_;
	std::mutex m_;
	size_t size_;
public:
    explicit ThreadPool(size_t poolSize)
    {
    	size_ = poolSize;
    	done_ = false;
    	for (size_t i = 0; i < size_; ++i) {
    		pool_.emplace_back([this]()
    		{
    			while(!done_) {
    				std::unique_lock<std::mutex> lock(m_);
    				if (tasks_.empty()) {
    					condition_.wait(lock);
    				} else {
    					auto task = tasks_.front();
    					tasks_.pop();
    					lock.unlock();
    					task();
    				}
    			}
    		});
    	}
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
    	auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
        std::unique_lock<std::mutex> lock(m_);
        tasks_.push([task]() {(*task)();});
        condition_.notify_one();
        return task->get_future();
    }

    ~ThreadPool()
    {
    	done_ = true;
    	condition_.notify_all();
    	for (size_t i = 0; i < size_; ++i) {
    		pool_[i].join();
    	}
    }
};