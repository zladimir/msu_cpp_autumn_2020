#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char separator = ' ';
    std::ostream& out;
    template <class T>
    Error process(T val);
    template <class T, class... ArgsT>
    Error process(T val, ArgsT... args);
    Error out_one(uint64_t num) const;
    Error out_one(bool b) const;
public: 
    explicit Serializer(std::ostream& out) : out(out){}
    template <class T>
    Error save(T& object);
    template <class... ArgsT>
    Error operator()(ArgsT ... args);
};

class Deserializer
{
    std::istream& in_;
    template <class T>
    Error process(T& val);
    template <class T, class... ArgsT>
    Error process(T& val, ArgsT&... args);
    Error in_one(bool& value) const;
    Error in_one(uint64_t& num) const;
public:
    explicit Deserializer(std :: istream& in) : in_(in) {}
    template <class T>
    Error load(T& object);
    template <class... ArgsT>
    Error operator()(ArgsT&... args);
};


template <class T>
Error Serializer::process(T val)
{
    return out_one(val);
}

template <class T, class... ArgsT>
Error Serializer::process(T val, ArgsT... args)
{
    const Error err = out_one(val);
    if (err == Error::NoError)
        return process(args...);
    return err;
}

Error Serializer::out_one(uint64_t num) const
{
    out << num << separator;
    return Error::NoError;
}

Error Serializer::out_one(bool b) const
{
    std :: string text;
    if (b == true)
        text = "true";
    else 
        text = "false";
    out << text << separator;
    return Error :: NoError;
}

template <class T>
Error Serializer::save(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT ... args)
{
    return process(args...);
}

template <class T>
Error Deserializer::process(T& val)
{
    return in_one(val);
}

template <class T, class... ArgsT>
Error Deserializer::process(T& val, ArgsT&... args)
{
    const Error err = in_one(val);
    if (err == Error::NoError)
        return process(args...);
    return err;
}

Error Deserializer::in_one(bool& value) const
{
    std::string text;
    in_ >> text;
    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;
    return Error::NoError;
}

Error Deserializer::in_one(uint64_t& num) const
{
    std::string text;
    in_ >> text;
    try
    {
        num = std::stoull(text);
        return Error::NoError;
    }
    catch(const std::logic_error &)
    {
        return Error::CorruptedArchive;
    }
}
    
template <class T>
Error Deserializer::load(T& object)
{
    return object.deserialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args)
{
    return process(args...);
}