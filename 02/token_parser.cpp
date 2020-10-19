#include "token_parser.h"
#include <iostream>

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

void TokenParser::TextParser(const std::string &text, int &digit_count, int &string_count){
	StartHandler_();
	digit_count = 0;
	string_count = 0;
	std::string cur_token;
	bool digit = true;
	int symbol = text[0];
	for (unsigned int i = 1; i <= text.length(); ++i)
	{
		if (isspace(symbol)) {
			if (!cur_token.empty()) {
				if (digit) {
					digit_count += DigitHandler_(cur_token);
				} else {
					string_count += StringHandler_(cur_token);
				}
				cur_token.clear();
				digit = true;
			}
		} else {
			if (!((symbol >= '0') && (symbol <= '9'))) {
				digit = false;
			}
			cur_token += symbol;
		}
		symbol = text[i];
	}
	if (!cur_token.empty()){
		if (digit) {
			digit_count += DigitHandler_(cur_token);
		} else {
			string_count += StringHandler_(cur_token);
		}
	}
	EndHandler_();
}