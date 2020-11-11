#include <iostream>
#include <sstream>
#include <cassert>
#include "serializer.hpp"

struct Data1
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct Data2
{
    uint64_t a;
    bool b;
    uint64_t c;
    bool d;
    bool e;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d, e);
    }
};

void test1()
{
    Data1 x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data1 y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test2()
{
    Data2 x { 1, true, 2, true, false };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data2 y { 0, false, 0, false, true };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.d == y.d);
    assert(x.e == y.e);
}

void test3()
{
    Data1 x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data2 y { 0, false, 0,true, false };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}

void test4()
{
    Data1 x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data1 y { 0, false, 0 };

    bool val;
    stream >> val;
    stream << 'a';

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    test4();
    std::cout << "Success" << std::endl;
}