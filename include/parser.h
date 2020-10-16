#ifndef CHEEM_PARSER_H
#define CHEEM_PARSER_H

#include <vector>
#include "object.h"
#include "token.h"

/**
 * @brief      This class collects the state of the tokens to be parsed
 */
class Reader {
	std::vector<Token> tokens;
public:
	unsigned int position;
	Reader(std::vector<Token> tokens);
	Token next();
	Token peek();
	bool is_at_end();
};

/**
 * @brief      parses tokens into an Object
 *
 * @param      reader  The reader
 *
 * @return     parsed token as an object
 */
Object* read_form(Reader& reader);

/**
 * @brief      parses an integer into an Object
 *
 * @param      reader  The reader
 *
 * @return     returns an integer object
 */
Object* read_integer(Reader& reader);

/**
 * @brief      parses a pair. Pair being an object that links to a head and tail (like a linked list node)
 *
 * @param      reader  The reader
 *
 * @return     parsed pair
 */
Object* read_pair(Reader& reader);

#endif