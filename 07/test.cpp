#include <iostream>
#include "myvector.hpp"
#include <cassert>

struct tricky
{
    int number;
    std::string str;
    tricky(int n, std::string s): number(n), str(std::move(s)) {}
    ~tricky() = default;
};

void test1()
{
    vector<int> v;
    int size = 100;
    for (int i = 0; i < size; ++i) {
        v.push_back(i);
    }
    assert(v[10] == 10);
    int i = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        assert(*it == size - 1 - i);
        i++;
    }
    int a = 3;
    v.push_back(std::move(a));
    assert(*(v.rbegin()) == 3);
}

void test2()
{
    vector<int64_t> v;
    v.reserve(3);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.resize(2);
    v.push_back(1);
    assert(v[2] == 1);
    v.clear();
    assert(v.empty());
    v.push_back(10);
    assert(v[0] == 10);
    v[0] = -5;
    assert(v[0] == -5);
}

void test3()
{
    vector<tricky> v;
    v.emplace_back(1, "a");
    v.emplace_back(2, "bb");
    v.emplace_back(3, "ccc");
    v.pop_back();
    v.emplace_back(4, "d");
    assert(v.size() == 3);
}

int main()
{
    test1();
    test2();
    test3();
    std::cout << "Success" << std::endl;
    return 0;
}