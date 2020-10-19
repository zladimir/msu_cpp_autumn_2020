#include <iostream>
#include <string>
#include <cassert>
#include "token_parser.h"

int DoubleCountingDigitHandler(std::string &digit)
{
	return 2;
}

int DoubleCountingStringHandler(std::string &digit)
{
	return 2;
}

void NewStartHandler()
{
	std::cout << "Set a new start handler" << std::endl;
}

void NewEndHandler()
{
	std::cout << "Set a new end handler" << std::endl;
}

void DefaultWorkTest()
{
	std::cout << "Test 1" << std::endl;
	int digit_count = 0;
	int string_count = 0;
	std::string s("\tAbracadabra\n254 as34 5432\n\tabc23");
	TokenParser tp;
	tp.TextParser(s, digit_count, string_count);
	assert(digit_count == 2 && string_count == 3);
}

void CustomTokenHandlersTest()
{
	std::cout << "Test 2" << std::endl;
	int digit_count = 0;
	int string_count = 0;
	std::string s("\tAbracadabra\n254 as34 5432\n\tabc23");
	TokenParser tp;
	tp.SetDigitTokenCallback(DoubleCountingDigitHandler);
	tp.SetStringTokenCallback(DoubleCountingStringHandler);
	tp.TextParser(s, digit_count, string_count);
	assert(digit_count == 4 && string_count == 6);
}

void CustomHandlersTest()
{
	std::cout << "Test 3" << std::endl;
	int digit_count = 0;
	int string_count = 0;
	std::string s("\tAbracadabra\n254 as34 5432\n\tabc23");
	TokenParser tp;
	tp.SetStartCallback(NewStartHandler);
	tp.SetEndCallback(NewEndHandler);
	tp.SetStringTokenCallback(DoubleCountingStringHandler);
	tp.TextParser(s, digit_count, string_count);
	assert(digit_count == 2 && string_count == 6);
}

int main(int argc, char const *argv[])
{
	DefaultWorkTest();
	CustomTokenHandlersTest();
	CustomHandlersTest();

	std::cout << "Success" << std::endl;

	return 0;
}