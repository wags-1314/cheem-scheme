#include <cstring>
#include <cctype>
#include <sstream>
#include "scanner.h"
#include "token.h"

Scanner::Scanner(std::string src) {
	source = src;
	start = 0;
	current = 0;
}

Token Scanner::scan_token() {
	skip_whitespace();
	start = current;

	if(is_at_end()) {
		return make_token_eof();
	}

	char ch = advance();

	if(isdigit(ch) || (ch == '-' && isdigit(peek()))) {
		return number();
	}

	if(ch == '#') {
		switch(peek()) {
			case 't':
			advance();
			return make_token_bool("#t");
			break;

			case 'f':
			advance();
			return make_token_bool("#f");
			break;

			case '\\':
			return character();
			break;
		}
	}

	if(ch == '"') {
		return string();
	}

	if(ch == '(') {
		return make_token_parenthesis();
	} else if (ch == ')'){
		return make_token_parenthesis(false);
	}

	if(ch == '.') {
		Token token;
		token.data = ".";
		token.type = TokenType::T_DOT;
		return token;
	}

	if(ch == '\'') {
		Token token;
		token.data = "'";
		token.type = TokenType::T_QUOTE;
		return token;
	}

	if(is_valid_symbol_character(ch)) {
		std::stringstream ss;
		ss << ch;
		while(!is_delimiter(ch = peek())) {
			ss << ch;
			advance();
		}
		std::string sym = ss.str();
		return make_token_symbol(sym);
	}

	return make_token_error("unknown character");
}

Token Scanner::string() {
	std::stringstream ss;
	char ch;
	while ((ch = advance()) != '"') {
		if(is_at_end()) {
			return make_token_error("string literal not terminated by \"");
		} if(ch == '\\') {
			ch = advance();
			if(ch == 'n') {
				ch = '\n';
			}
		}
		ss << ch;
	}
	std::string string = ss.str();
	return make_token_string(string);
}

bool Scanner::eat_expected_string(std::string check) {
    char ch;
    for(unsigned int i = 0; i < check.length(); i++) {
    	ch = advance();
    	if(ch != check[i]) {
    		return false;
    	}
    }
    return true;
}

 bool is_delimiter(char ch) {
 	return ch == ' ' || ch == '\r' || ch == '\t' || ch == '\0' || ch == '('  || ch == ')' || ch == '.'; //TODO: need to add brackets and semicolons
 }


Token Scanner::character() {
	advance();
	if(is_at_end()) {
		return make_token_error("incomplete character literal");
	}
	char ch = advance();
	switch(ch) {
		case 's':
		if(peek() == 'p') {
			bool flag = eat_expected_string("pace");
			if(flag) {
				if(is_delimiter(peek())) {
					return make_token_character("#\\space");
				} else {
					return make_token_error("needs to end with a delimiter");
				}

				return make_token_error("unexpected character");
			}
		}
		break;

		case 'n':
		if(peek() == 'e') {
			bool flag = eat_expected_string("ewline");
			if(flag) {
				if(is_delimiter(peek())) {
					return make_token_character("#\\newline");
				} else {
					return make_token_error("needs to end with a delimiter");
				}

				return make_token_error("unexpected character");
			}
		}
		break;
	}

	return make_token_character(std::string(1, ch));
}

void Scanner::skip_whitespace() {
	while(true) {
		char ch = peek();
		switch(ch) {
			case ' ':
			case '\r':
			case '\t':
			advance(); break;

			default:
			return;
		}
	}
}

bool Scanner::is_at_end() {
	return current == source.length();
}

char Scanner::advance() {
	current += 1;
	return source[current - 1];
}

char Scanner::peek() {
	return source[current];
}

Token Scanner::number() {
	while(isdigit(peek()))
		advance();

	return make_token_int(std::string(source.substr(start, current - start)));
}

std::vector<Token> Scanner::scan_tokens() {
	Token token;
	std::vector<Token> tokens;
	do {
		token = scan_token();
		tokens.push_back(token);
	} while(token.type != TokenType::T_EOF);

	tokens.pop_back();
	return tokens;
}

bool is_valid_symbol_character(char ch) {
	if(isalpha(ch)) {
		return true;
	} else {
		switch(ch) {
			case '!': case '$': case '%': case '&': case '*': case '+': case '-':
			case '/': case ':': case '<': case '=': case '>': case '?': case '@': 
			case '^': case '_': case '~':
			return true;
			break;

			default:
			return false;
		}
	}
}

/*int main(int argc, char const *argv[]) {
	Scanner scanner = Scanner("abcd efgh");
	auto tokens = scanner.scan_tokens();
	for(auto token: tokens) {
		std::cout << token << std::endl;
	}
	return 0;
}*/

