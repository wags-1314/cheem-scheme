#ifndef CHEEM_TOKEN_H
#define CHEEM_TOKEN_H

#include <string>
#include <iostream>

/**
 * @brief      This class describes a token type.
 */
enum class TokenType {
	T_QUOTE, T_INT, T_BOOL, T_ERROR, T_EOF, T_CHAR, T_STRING,
	T_LPAREN, T_RPAREN, T_DOT, T_SYMBOL
};

/**
 * @brief      This struct describes a lexical Token
 */
struct Token {
	TokenType type;
	std::string data;
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

Token make_token_int(std::string integer);
Token make_token_error(std::string error_message);
Token make_token_eof();
Token make_token_bool(std::string boolean);
Token make_token_character(std::string character);
Token make_token_string(std::string string);
Token make_token_parenthesis(bool is_left_paren=true);
Token make_token_symbol(std::string symbol);

#endif