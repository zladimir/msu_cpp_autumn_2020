#pragma once
#include <sstream>
#include <vector>
#include <exception>
#include <string>
#include <cctype>

using parametr_vector = std::vector<std::string>;

class InvalidString: public std::exception
{
    std::string error;
public:
    InvalidString(std::string err) noexcept: error(err) {}
    const char* what() const noexcept override 
    {
        return error.c_str();
    } 
};

class InvalidPosition: public std::exception
{
    std::string error;
public:
    InvalidPosition(std::string err) noexcept: error(err) {}
    const char* what() const noexcept override 
    {
        return error.c_str();
    } 
};


template<class T>
void process(parametr_vector &params, const T& val)
{
    std::ostringstream ss;
    ss << val;
    params.push_back(ss.str());
}

template<class T, class... ArgsT>
void process(parametr_vector &params, const T& val, const ArgsT&... args)
{
    process(params, val);
    process(params, args...);
}

template<class... ArgsT>
std::string format(const std::string& s, const ArgsT&... args)
{
    parametr_vector params;
    process(params, args...);
    std::string result;
    std::string arg;
    bool assembly_arg = false;
    for (size_t i = 0; i < s.length(); ++i) {
        const char &symbol = s[i];
        switch(symbol) {
        case '{':
            if (assembly_arg) {
                throw InvalidString("The previous arg is incomplete");
            }
            assembly_arg = true;
            break;
        case '}':
            if (!assembly_arg) {
                throw InvalidString("Symbol '}' out of context");
            }
            try {
                size_t n = std::stoull(arg);
                result += params.at(n);
            }
            catch(const std::out_of_range&) {
                throw InvalidPosition("Arg with this number wasn\'t found");
            }
            arg.clear();
            assembly_arg = false;
            break;
        default:
            if (assembly_arg) {
                if (isdigit(symbol)) {
                    arg += symbol;
                } else {
                    throw InvalidString("Argument must be a number of size_t");
                }
            } else {
                result.push_back(symbol);
            }
        }
    }
    if (assembly_arg) {
        throw InvalidString("The closing symbol wasn\'t found");
    }
    return result;
}