#include "token_parser.h"
#include <iostream>
#include <cctype>

int DefaultDigitHandler(std::string &digit)
{
	return 1;
}

int DefaultStringHandler(std::string &s)
{
	return 1;
}

void DefaultStartHandler() {}

void DefaultEndHandler() {}

TokenParser::TokenParser()
{
	DigitHandler_ = DefaultDigitHandler;
	StringHandler_ = DefaultStringHandler;
	StartHandler_ = DefaultStartHandler;
	EndHandler_ = DefaultEndHandler;
}

void TokenParser::SetStartCallback(handler_ptr start)
{
	StartHandler_ = start;
}

void TokenParser::SetEndCallback(handler_ptr end)
{
	EndHandler_ = end;
}

void TokenParser::SetDigitTokenCallback(token_handler_ptr custom_digit_handler)
{
	DigitHandler_ = custom_digit_handler;
}

void TokenParser::SetStringTokenCallback(token_handler_ptr custom_string_handler)
{
	StringHandler_ = custom_string_handler;
}

void TokenParser::ChooseTokenHandler(std::string &token, bool digit, int &digit_count, int &string_count)
{
	if (digit) {
		digit_count += DigitHandler_(token);
	} else {
		string_count += StringHandler_(token);
	}
}

void TokenParser::TextParser(const std::string &text, int &digit_count, int &string_count){
	StartHandler_();
	digit_count = 0;
	string_count = 0;
	std::string cur_token;
	bool digit = true;
	int symbol;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		symbol = text[i];
		if (isspace(symbol)) {
			if (!cur_token.empty()) {
				ChooseTokenHandler(cur_token, digit, digit_count, string_count);
				cur_token.clear();
				digit = true;
			}
		} else {
			if (!isdigit(symbol)) {
				digit = false;
			}
			cur_token += symbol;
		}
	}
	if (!cur_token.empty()){
		ChooseTokenHandler(cur_token, digit, digit_count, string_count);
	}
	EndHandler_();
}