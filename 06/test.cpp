#include <iostream>
#include <cassert>
#include "format.hpp"

void test1()
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void test2()
{
    char a = 'y';
    std::string b("qwe");
    std::string c("rt");
    std::string text = format("{1}{2}{0}", a, b, c);
    assert(text == "qwerty");
}

void test3()
{
    float a = 3.3;
    float b = 6.6;
    try {
        auto text = format("a = {0}, b = {{1}", a, b);
    }
    catch(const InvalidString& e) {
        std::string expected("The previous arg is incomplete");
        assert(expected == e.what());
    }
}

void test4()
{
    float a = 3.3;
    bool b = true;
    char c = 'c';
    try {
        auto text = format("char {2}, bool {1}, float {0}, unknow{3}", a, b, c);
    }
    catch(const InvalidPosition& e) {
        std::string expected("Arg with this number wasn't found");
        assert(expected == e.what());
    }
}

void test5()
{
    int a = 2;
    float b = 3.3;
    try {
        auto text = format("float {1} + int{number}", a, b);
    }
    catch(const InvalidString& e) {
        std::string expected("Argument must be a number of size_t");
        assert(expected == e.what());
    }
}

void test6()
{
    int a = 2;
    float b = 3.3;
    try {
        auto text = format("float {1} + int{1.1}", a, b);
    }
    catch(const InvalidString& e) {
        std::string expected("Argument must be a number of size_t");
        assert(expected == e.what());
    }
}

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    std::cout << "Success" << std::endl;
    return 0;
}