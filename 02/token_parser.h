#include <iostream>

using token_handler_ptr = int(*)(std::string &);
using handler_ptr = void(*)();

int DefaultDigitHandler(std::string &);
int DefaultStringHandler(std::string &);
void DefaultStartHandler();
void DefaultEndHandler();

class TokenParser
{
	token_handler_ptr DigitHandler_, StringHandler_;
	handler_ptr StartHandler_, EndHandler_;
public:
	TokenParser();
	void SetStartCallback(handler_ptr);
	void SetEndCallback(handler_ptr);
	void SetDigitTokenCallback(token_handler_ptr);
	void SetStringTokenCallback(token_handler_ptr);
	void TextParser(const std::string &, int &, int &);
};