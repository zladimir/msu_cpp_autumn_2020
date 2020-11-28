#include <iostream>
#include <string>
#include "myvector.hpp"
#include <cassert>

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
    vector<std::string> v;
    v.emplace_back("abc", 2);
    v.emplace_back("def", 3);
    v.emplace_back("jh", 1);
    v.pop_back();
    v.emplace_back("qwerty", 6);
    assert(v.size() == 3);
}

void test4()
{
    vector<int> v;
    for (int i = 0; i < 16; ++i) {
        v.push_back(i);
    }
    vector<int> w = std::move(v);
    vector<int> z;
    for (int i = 0; i < 16; ++i) {
        z.push_back(i-16);
    }
    z = w;
    for (size_t i = 0; i < z.size(); ++i) {
        assert(z[i] == w[i]);
    }
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    std::cout << "Success" << std::endl;
    return 0;
}