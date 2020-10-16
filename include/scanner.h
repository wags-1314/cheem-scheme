#ifndef CHEEM_SCANNER_H
#define CHEEM_SCANNER_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "token.h"

/**
 * @brief      This class describes a scanner that tokenizes an incoming string
 */
class Scanner {
	std::string source;
	unsigned int start;
	unsigned int current;
	bool is_at_end();
	char advance(); //!moves to the next character
	void skip_whitespace();
	char peek();
	Token number(); //! generates a integer type token
	bool match(char ch);
	Token character(); //! generates a character type token
	bool eat_expected_string(std::string stri); //! consumes the string if it exists in the source string
	Token string();
public:
	Scanner(std::string src);
	/**
	 * @brief      scans the next token
	 *
	 * @return     token that has been scanned
	 */
	Token scan_token();
	/**
	 * @brief      returns all tokens in a std::vector<Token>
	 *
	 * @return     std::vector of all tokens
	 */
	std::vector<Token> scan_tokens();
};

bool is_delimiter(char ch);
bool is_valid_symbol_character(char ch);

#endif