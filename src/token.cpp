#include "token.h"

std::ostream& operator<<(std::ostream& os, const  Token& token) {
	os << "Token{ ";

	switch(token.type) {
		case TokenType::T_INT:
		os << "integer, ";
		break;

		case TokenType::T_ERROR:
		os << "error, ";
		break;

		case TokenType::T_EOF:
		os << "eof";
		break;

		case TokenType::T_CHAR:
		os << "character, ";
		break;

		case TokenType::T_BOOL:
		os << "boolean, ";
		break;

		case TokenType::T_STRING:
		os << "string, ";
		break;

		case TokenType::T_LPAREN:
		os << "string, ";
		break;

		case TokenType::T_RPAREN:
		os << "string, ";
		break;

		case TokenType::T_DOT:
		os << "dot, ";

		case TokenType::T_SYMBOL:
		os << "symbol, ";

		case TokenType::T_QUOTE:
		os << "quote, ";
	}

	os << token.data << " }";
	return os;
}

Token make_token_int(std::string integer) {
	Token token;
	token.type = TokenType::T_INT;
	token.data = integer;
	return token;
}

Token make_token_error(std::string error_message) {
	Token token;
	token.type = TokenType::T_ERROR;
	token.data = error_message;
	return token;
}

Token make_token_eof() {
	Token token;
	token.type = TokenType::T_EOF;
	return token;
}

Token make_token_bool(std::string boolean) {
	Token token;
	token.type = TokenType::T_BOOL;
	token.data = boolean;
	return token;
}

Token make_token_character(std::string character) {
	Token token;
	token.type = TokenType::T_CHAR;
	token.data = character;
	return token;
}

Token make_token_string(std::string string) {
	Token token;
	token.type = TokenType::T_STRING;
	token.data = string;
	return token;
}

Token make_token_parenthesis(bool is_left_paren) {
	Token token;
	if(is_left_paren) {
		token.type = TokenType::T_LPAREN;
		token.data = "(";
	} else {
		token.type = TokenType::T_RPAREN;
		token.data = ")";
	}

	return token;
}

Token make_token_symbol(std::string symbol) {
	Token token;
	token.type = TokenType::T_SYMBOL;
	token.data = symbol;
	return token;
}

/*int main(int argc, char const *argv[]) {
	Token token;
	token.type = TokenType::T_QUOTE;
	token.data = "'";
	std::cout << token;
	return 0;
}*/