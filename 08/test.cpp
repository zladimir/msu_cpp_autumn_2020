#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "thread_pool.hpp"

struct A {};

void f(const A &) {}

void sleep_func()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test1() 
{
    ThreadPool pool(4);
    auto task0 = pool.exec(f, A());

    int s = 1;
    auto task1 = pool.exec([s]() { return s; });
    assert(task1.get() == 1);

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);

    auto task3 = pool.exec([s]() { return s + 2; });
    assert(task3.get() == 3);

    auto task4 = pool.exec(sleep_func);
    for(int i = 0; i < 10; ++i)
    {
        assert(pool.exec([i]() { return i; }).get() == i);
    }
}

int main(int argc, char const *argv[])
{
	test1();
	std::cout << "Success" << std::endl;
	return 0;
}