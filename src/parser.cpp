#include "parser.h"
#include "scanner.h"
#include <string>

Reader::Reader(std::vector<Token> tokens_) {
	tokens = tokens_;
	position = 0;
}

Token Reader::next() {
	position += 1;
	return tokens[position - 1];
}

Token Reader::peek() {
	if(!is_at_end()) {
		return tokens[position];
	} else {
		return make_token_eof();
	}
}

bool Reader::is_at_end() {
	return position >= tokens.size();
}

Object* read_form(Reader& reader) {
	Token token = reader.peek();
	if(token.type == TokenType::T_INT) {

		return read_integer(reader);

	} if (token.type == TokenType::T_BOOL) {

		token = reader.next();
		if(token.data.compare("#t") == 0) {
			return Constants::True;
		} else {
			return Constants::False;
		}

	} if (token.type == TokenType::T_CHAR) {

		token = reader.next();
		if(!token.data.compare("#\\newline")) {
			return make_object_character('\n');
		} else if(!token.data.compare("#\\space")) {
			return make_object_character(' ');
		} else {
			return make_object_character(token.data[0]);
		}

	} if (token.type == TokenType::T_STRING) {

		token = reader.next();
		return make_object_string(token.data);

	} if (token.type == TokenType::T_LPAREN) {
		reader.next();
		return read_pair(reader);
	} if (token.type == TokenType::T_QUOTE) {
		reader.next();
		Object* object = new Object();
		object->type = ObjectType::O_SYMBOL;
		object->string = "quote";
		return cons(object, read_form(reader));
	} if (token.type == TokenType::T_SYMBOL) {
		token = reader.next();
		return make_object_symbol(token.data);
	}
}

Object* read_integer(Reader& reader) {
	Token token = reader.next();
	long data = std::stol(token.data);
	return make_object_integer(data);
}

Object* read_pair(Reader& reader) {
	Object* car;
	Object* cdr;

	Token token = reader.peek();
	if(token.type == TokenType::T_RPAREN) {
		reader.next(); // remove the ')'
		return Constants::Null;
	}

	car = read_form(reader);
	token = reader.peek();
	if(token.type == TokenType::T_DOT) {
		reader.next(); // remove the '.'
		cdr = read_form(reader);
		token = reader.peek();
		return cons(car, cdr);
	} else {
		cdr = read_pair(reader);
		return cons(car, cdr);
	}

}

/*int main(int argc, char const *argv[]) {
	Scanner scanner("(1 2)");
	auto tokens = scanner.scan_tokens();
	for(auto token : tokens) {
		std::cout << token << std::endl;
	}

	std::cout << std::endl;

	Reader reader(tokens);
	Object* object = read_form(reader);
	std::cout << "(" << object->car->integer << " ";
	std::cout << object->cdr->car->integer << ")";
	return 0;
}*/