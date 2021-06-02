#ifndef CHEEM_OBECT_H
#define CHEEM_OBECT_H

#include <string>
#include <iostream>

/**
 * @brief      This class describes all object types
 */
enum class ObjectType {
	O_INTEGER, O_BOOL, O_CHARACTER, O_ERROR, O_STRING, O_NULL, O_DEFAULT,
	O_PAIR, O_SYMBOL, O_PPROC, O_PROC
};

/**
 * @brief      utility function to print the ObjectType as a string
 *
 * @param[in]  type  The type
 * @param      out   output stream
 */
void print_object_type(ObjectType type, std::ostream& out);

/**
 * @brief      Generic cheem-scheme object
 */
class Object {
public:
	ObjectType type;
	long integer;
	bool boolean;
	char character;
	std::string string;
	Object* car; //! head of pair
	Object* cdr; //! tail of pair
	Object* (*func)(Object* arguments);

	Object() { type = ObjectType::O_DEFAULT; }
	Object(ObjectType type_){ type = type_; }
	Object(bool boolean_) { type = ObjectType::O_BOOL; boolean = boolean_; }

};

/**
 * @brief      Some obect constants that will be used a lot
 */
class Constants {
public:
	static Object* Null;
	static Object* False;
	static Object* True;
};

Object* make_object_integer(long integer);
Object* make_object_bool(bool boolean);
Object* make_object_character(char ch);
Object* make_object_string(std::string string);

/**
 * @brief      forms a pair like this: car -> cdr
 *
 * @param      car   The car
 * @param      cdr   The cdr
 *
 * @return     returns formed pair
 */
Object* cons(Object* car, Object* cdr);
Object* make_object_symbol(std::string symbol);
Object* make_object_error(std::string error_message);
Object* make_object_primitive_procedure(Object* (*func)(Object* arguments));
Object* make_object_procedure(Object* params, Object* body);

bool is_integer(Object *obj);
bool is_boolean(Object* obj);
bool is_character(Object* obj);
bool is_string(Object* obj);
bool is_null(Object* obj);
bool is_true(Object* obj);
bool is_pair(Object* obj);
bool is_symbol(Object* obj);
bool is_error(Object* obj);
bool is_primitive_procedure(Object* obj);
bool is_procedure(Object* obj);

/**
 * @brief      returns head of pair
 *
 * @param      pair  The pair
 *
 * @return     head of pair
 */
Object* car(Object* pair);

/**
 * @brief      returns tail of pair
 *
 * @param      pair  The pair
 *
 * @return     tail of pair
 */
Object* cdr(Object* pair);

#endif